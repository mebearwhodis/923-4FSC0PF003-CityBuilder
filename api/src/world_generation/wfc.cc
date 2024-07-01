#include <world_generation/wfc.h>

WFC::WFC(unsigned width, unsigned height): width_(width), height_(height),
                                           wave_(width* height, std::set<TileType>())
{
	// Initialize the wave function with all possible tiles
	for (auto& cell : wave_) {
		for (int i = 0; i < static_cast<int>(TileType::kLength); ++i) {
			cell.insert(static_cast<TileType>(i));
		}
	}
}

void WFC::generate(std::vector<TileType>& output)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Priority queue to propagate constraints
	std::queue<std::pair<int, int>> propagationQueue;

	while (!isCollapsed()) {
		// Step 1: Find the cell with the least entropy
		int cellIdx = findCellWithLeastEntropy(gen);
		if (cellIdx == -1) break;

		// Step 2: Collapse the cell to a single state
		collapseCell(cellIdx, gen);

		// Step 3: Propagate constraints
		propagate(cellIdx, propagationQueue, gen);
	}

	// Copy the result to the output vector
	output.resize(width_ * height_);
	for (unsigned int i = 0; i < wave_.size(); ++i) {
		if (!wave_[i].empty()) {
			output[i] = *wave_[i].begin();
		}
	}
}

bool WFC::isCollapsed() const
{
	return std::all_of(wave_.begin(), wave_.end(), [](const std::set<TileType>& cell) {
		return cell.size() == 1;
	});
}

int WFC::findCellWithLeastEntropy(std::mt19937& gen) const
{
	int minEntropy = std::numeric_limits<int>::max();
	std::vector<int> minEntropyCells;

	for (unsigned int i = 0; i < wave_.size(); ++i) {
		if (wave_[i].size() > 1 && static_cast<int>(wave_[i].size()) < minEntropy) {
			minEntropy = wave_[i].size();
			minEntropyCells.clear();
			minEntropyCells.push_back(i);
		}
		else if (wave_[i].size() == minEntropy) {
			minEntropyCells.push_back(i);
		}
	}

	if (minEntropyCells.empty()) return -1;
	std::uniform_int_distribution<> dis(0, minEntropyCells.size() - 1);
	return minEntropyCells[dis(gen)];
}

void WFC::collapseCell(int idx, std::mt19937& gen)
{
	if (wave_[idx].size() <= 1) return;

	std::vector<TileType> possibleStates(wave_[idx].begin(), wave_[idx].end());
	std::uniform_int_distribution<> dis(0, possibleStates.size() - 1);
	TileType selectedState = possibleStates[dis(gen)];

	wave_[idx].clear();
	wave_[idx].insert(selectedState);
}

void WFC::propagate(int startIdx, std::queue<std::pair<int, int>>& propagationQueue, std::mt19937& gen)
{
	int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	propagationQueue.push({ startIdx, 0 });

	while (!propagationQueue.empty()) {
		auto [idx, dir] = propagationQueue.front();
		propagationQueue.pop();

		int x = idx % width_;
		int y = idx / width_;

		for (int d = 0; d < 4; ++d) {
			int nx = x + directions[d][0];
			int ny = y + directions[d][1];

			if (nx < 0 || ny < 0 || nx >= width_ || ny >= height_) continue;
			int nidx = ny * width_ + nx;

			std::set<TileType> compatibleStates;
			for (TileType tile : wave_[idx]) {
				const auto& rules = adjacencyRules.at(tile);
				switch (d) {
				case 0: compatibleStates.insert(rules.right.begin(), rules.right.end()); break;
				case 1: compatibleStates.insert(rules.left.begin(), rules.left.end()); break;
				case 2: compatibleStates.insert(rules.bottom.begin(), rules.bottom.end()); break;
				case 3: compatibleStates.insert(rules.top.begin(), rules.top.end()); break;
				}
			}

			std::set<TileType> newStates;
			std::set_intersection(
				wave_[nidx].begin(), wave_[nidx].end(),
				compatibleStates.begin(), compatibleStates.end(),
				std::inserter(newStates, newStates.begin())
			);

			if (newStates.size() != wave_[nidx].size()) {
				wave_[nidx] = newStates;
				if (wave_[nidx].size() == 1) {
					propagationQueue.push({ nidx, d });
				}
			}
		}
	}
}
