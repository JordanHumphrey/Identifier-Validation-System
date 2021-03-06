// Identifier Links.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>
#include <set>

class Verification {
private:
	std::vector<std::pair<std::string, std::string>> confirmedLinks;
	std::vector<std::pair<std::string, std::string>> seenLinks;
	std::queue<std::pair<std::string, std::string>> linksToProcess;

public:
	void addLink(std::string id1, std::string id2) {
		confirmedLinks.push_back(std::make_pair(id1, id2));
	}

	// Check to see if the link has been seen already
	bool isSeen(std::pair<std::string, std::string> search) {
		for (auto& link : seenLinks) {
			if (link.first == search.first &&
				link.second == search.second) {
				return true;
			}
		}
		return false;
	}

	// Reset environment between searches
	void Reset() {
		seenLinks.clear();
		while (!linksToProcess.empty())
			linksToProcess.pop();
	}

	bool isLinked(std::string id1, std::string id2) {
		// search the links we know are confirmed
		for (auto& link : confirmedLinks) {
			if (link.first == id1 && link.second == id2)
				return true;
		}

		// we have not seen it yet, begin search

		linksToProcess.emplace(std::make_pair(id1, id2));



		// process each of the links in the queue to find 
		// the path we are looking for to id2
		while (!linksToProcess.empty()) {
			std::pair<std::string, std::string> linkToCheck = linksToProcess.front();
			linksToProcess.pop();


			// check if we have seen this link before
			// if we have not seen this one before
			if (!isSeen(linkToCheck)) {

				// first, lets add this link to seenLinks
				seenLinks.push_back(linkToCheck);

				// now lets look for the link to see if we found it
				if (linkToCheck.second == id2 && linkToCheck.first != id1) {
					return true;
				}

				// we didnt see it, add next links to check in the list
				for (auto& link : confirmedLinks) {
					if (linkToCheck.first == link.first || linkToCheck.second == link.first && !isSeen(link)) {
						linksToProcess.emplace(link);
					}
				}
			}
		}

		// we never found it, return false;
		return false;
	}

	void removeId(std::string id) {
		for (auto it = confirmedLinks.begin(); it != confirmedLinks.end(); ++it) {
			if (it->first == id || it->second == id) {
				it = confirmedLinks.erase(it);
			}
		}
	}
};




int main()
{
	std::set<std::pair<std::string, std::string>> linksToCheck;
	linksToCheck.insert(std::make_pair("markus", "christina"));
	linksToCheck.insert(std::make_pair("sarah", "christina"));
	linksToCheck.insert(std::make_pair("markus", "jordan"));

	Verification verify;
	verify.addLink("sarah", "jason");
	verify.addLink("jason", "jordan");
	verify.addLink("jordan", "sam");
	verify.addLink("anna", "markus");
	verify.addLink("sam", "markus");
	verify.addLink("sam", "saul");
	verify.addLink("sam", "mike");
	verify.addLink("mike", "christina");
	verify.addLink("markus", "sam");
	
	for (auto pair : linksToCheck) {
		auto result = verify.isLinked(pair.first, pair.second);
		if (result)
			verify.addLink(pair.first, pair.second);
		verify.Reset();
	}

	return 0;
}
