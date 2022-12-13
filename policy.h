#include "MCTS.h"
#include "LeafParellelMCTS.h"
#include "RootParellelMCTS.h"
#include "TreeParellelMCTS.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
class episode;

class Policy {
public:
	Policy() = delete;
	

	static Pair Greedy (const board &before, const PIECE &piece) {
		
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::cout << "Greedy take action\n";
		if ( before.check_Piece_onBoard(piece) == FAIL ) return {};
		//find whether can eat piece or not
		board tmp = before;
		std::vector<Pair> pos = tmp.find_piece(piece, EAT);
		if ( !pos.empty() ) {
			// take eat action first
			return pos[0];	
		}
		else {
			//take move action second
			pos = tmp.find_piece(piece, MOVE);
			if ( !pos.empty() ) {
				std::shuffle(pos.begin(), pos.end(), engine);
				return pos[0];
			}
		}
		return {};

	}
	static Pair Manual (const board &before, const PIECE &piece) {
		board tmp = before;
		auto moves = tmp.get_available_move(piece);
		std::cout << "Available moves: \n";
		int cnt = 0;
		for(auto &mv_pair : moves) {
			std::cout << "(" << std::setw(2) << int(mv_pair.prev) << ", " << std::setw(2) << int(mv_pair.next) << ") ";
			if (++cnt % 4 == 0){
				std::cout << '\n';
				cnt = 0;
			}
		}
		std::cout << '\n';
		std::cout << "Please input moves: (format:pos1, pos2)\n";
		int x1, x2;
		std::cin >> x1 >> x2;
		
		return {x1, x2};
	}

	static Pair MCTS (board &before, const PIECE &piece, const int &simulation_times) {
		if ( before.check_Piece_onBoard(piece)==FAIL ) return {};//lose
		
		MonteCarloTree tree;
		tree.reset(before);
		std::cout << "MCTS take action\n";
		const int &simulationtime = simulation_times;
		int count_sim = 0;
		while (count_sim < simulationtime) {
			tree.tree_policy();
			count_sim++;
		}
		
		// tree.root->showchild();

		Pair best_move = tree.root->best_child();
		return best_move;
	}

	static Pair leaf_parallel_MCTS (board &before, const PIECE &piece, const int &simulation_times) {
		if ( before.check_Piece_onBoard(piece)==FAIL ) return {};//lose
		
		MonteCarloTree tree;
		tree.reset(before);
		std::cout << "leaf_parallel_MCTS take action\n";
		const int &simulationtime = simulation_times;
		int count_sim = 0;
		while (count_sim < simulationtime) {
			tree.tree_policy();
			count_sim++;
		}
		
		// tree.root->showchild();

		Pair best_move = tree.root->best_child();
		return best_move;
	}

	static Pair root_parallel_MCTS (board &before, const PIECE &piece, const int &simulation_times) {
		if ( before.check_Piece_onBoard(piece)==FAIL ) return {};//lose
		
		MonteCarloTree tree;
		tree.reset(before);
		std::cout << "root_parallel_MCTS take action\n";
		const int &simulationtime = simulation_times;
		int count_sim = 0;
		while (count_sim < simulationtime) {
			tree.tree_policy();
			count_sim++;
		}
		
		// tree.root->showchild();

		Pair best_move = tree.root->best_child();
		return best_move;
	}

	static Pair tree_parallel_MCTS (board &before, const PIECE &piece, const int &simulation_times) {
		if ( before.check_Piece_onBoard(piece)==FAIL ) return {};//lose
		
		MonteCarloTree tree;
		tree.reset(before);
		std::cout << "tree_parallel_MCTS take action\n";
		const int &simulationtime = simulation_times;
		int count_sim = 0;
		while (count_sim < simulationtime) {
			tree.tree_policy();
			count_sim++;
		}
		
		// tree.root->showchild();

		Pair best_move = tree.root->best_child();
		return best_move;
	}
};
