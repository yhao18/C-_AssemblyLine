#include <algorithm>
#include "LineManager.h"

namespace sdds{

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		Utilities utility;
		size_t next_pos;
		bool more;
		std::string data, currentStationName, nextStationName;
		

		std::for_each(stations.begin(), stations.end(), [](Workstation* s) {s->setNextStation(); });

		std::ifstream ifile(file);
		if (!ifile.is_open())
			throw std::string("ERROR: Failed to open the file [" + file + "].");

		while (!ifile.eof()) {
			next_pos = 0;
			more = true;

			std::getline(ifile, data);
			currentStationName = utility.extractToken(data, next_pos, more);
			auto currentStation = std::find_if(stations.begin(), stations.end(), [=](const Workstation* s) {return s->getItemName() == currentStationName; });

			if (currentStation == stations.end())
				throw std::string("ERROR: Current Station name not found [" + currentStationName + "]\n");

			activeLine.push_back(*currentStation);

			if (more) {
				nextStationName = utility.extractToken(data, next_pos, more);
				auto nextStation = std::find_if(stations.begin(), stations.end(), [nextStationName](const Workstation* s) {return s->getItemName() == nextStationName; });

				if(nextStation == stations.end())
					throw std::string("ERROR: Next Station name not found [" + nextStationName + "]\n");
				if(nextStation == currentStation)
					throw std::string("ERROR: Next Station [" + nextStationName + "] is the current station [" + currentStationName +"]\n");

				(*currentStation)->setNextStation(*nextStation);
				}
			}
	
		ifile.close();

		std::for_each(activeLine.begin(), activeLine.end(), [this](Workstation* test) {
			auto found = std::find_if(activeLine.begin(), activeLine.end(), [&test](Workstation* s) {
				return s->getNextStation() == test; });
			if (found == activeLine.end()) {
				if (m_firstStation)
					throw std::string("ERROR: First station ambiguous\n");
				else
					m_firstStation = test;
			}
			});
		if (!m_firstStation) {
			throw std::string("ERROR: First station not found\n");
		}

		m_cntCustomerOrder = pending.size();


	}

	void LineManager::linkStations()
	{
		std::vector<Workstation*> temp;

		auto ptr = m_firstStation;
		while (ptr) {
			temp.push_back(ptr);
			ptr = ptr->getNextStation();
		}

		activeLine = temp;
	}

	bool LineManager::run(std::ostream& os)
	{
		static size_t cnt = 0;
		os << "Line Manager Iteration: " << ++cnt << std::endl;

		if (!pending.empty()) {
			*m_firstStation += std::move(pending.front());
			pending.pop_front();
		}

		for (auto& s : activeLine) {
			s->fill(os);
		}

		for (auto& s : activeLine) {
			s->attemptToMoveOrder();
		}

		bool count = completed.size() + incomplete.size() == m_cntCustomerOrder;
		return count;
	}

	void LineManager::display(std::ostream& os) const
	{
		for (const auto& s : activeLine)
			s->display(os);
	}



}

