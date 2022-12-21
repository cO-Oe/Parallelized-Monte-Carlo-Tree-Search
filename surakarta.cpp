/**

The main program of Surakarta Game
------------------------------------------
This is the Project of Surakarta Game AI

Construced by Clive Wu and Mark Chang
Instructed by Professor I-Chen Wu

**/
#include <iterator>
#include <unistd.h>
#include <typeinfo> 
#include <fstream>

#include "agent.h"
#include "episode.h"
#include "statistic.h"

void man_help() {
	std::cout << "Usage: ./surakarta [OPTION]...\n\n";
	std::cout << "A Surakarta Game Engine implementing different strategy, ex: Greedy, MCTS, AlphaGo(disabled), enjoy it!\n\n";
	
	std::cout << "[OPTION]...\n";
	std::cout << std::left << std::setw(30);
	std::cout << "  --total=NUM_OF_GAME" << "Set total numbers of games to run. Default value: 5\n\n";
	std::cout << std::left << std::setw(30);
	std::cout << "  --mode=MODE" << "Two Modes: \"train\" for training (disabled),  \"eval\" for evaluation.\n" << std::setw(30) << " " << "Default value: \"eval\"\n\n";
	std::cout << std::left << std::setw(30);
	std::cout << "  --black=POLICY" << "Three POLICYS: \"Greedy\", \"MCTS\", \"OpenmpMCTS\", \"RootParallelMCTS\", \"TreeParallelMCTS\", \"Manual\" to choose.\n";
	std::cout << std::left << std::setw(30);
	std::cout << "  --white=POLICY" << "\n\n";
}

int main(int argc, char* argv[]) {
	std::cout << "Surakarta Demo: ";
	std::copy(argv, argv + argc, std::ostream_iterator<char *>(std::cout, " "));
	std::cout << "\n\n";

	size_t total = 5, block = 0;
	std::string load_module;
	std::string save_module;
	std::string mode = "eval";
	std::string black_policy = "OpenmpMCTS";
	std::string white_policy = "MCTS";
	
	for (int i{1}; i < argc; i++) {
		std::string para(argv[i]);
		if (para.find("--help") == 0) {
			man_help();
			return 0;
		}
		else if (para.find("--total=") == 0) {
			total = std::stoull(para.substr(para.find("=") + 1));
		}
		else if (para.find("--block=") == 0) {
			block = std::stoull(para.substr(para.find("=") + 1));
		}
		else if (para.find("--mode=") == 0) {
			mode = para.substr(para.find("=") + 1);
		}
		else if (para.find("--black=") == 0) {
			black_policy = para.substr(para.find("=") + 1);
		}
		else if (para.find("--white=") == 0) {
			white_policy = para.substr(para.find("=") + 1);
		}
	}

	statistic stat(total, block);

	player play {BLACK, black_policy};  // 0
	envir env {WHITE, white_policy};  // 1
	int cnt = 0;
	episode train_set_game;
	int save_cnt = 0;

	while (!stat.is_finished()) {

		board b;

		stat.open_episode("W:B");
		episode& game = stat.back(); 
		std::cout << b << '\n';
		while ( true ) {
			// player first (left)
			agent& who = game.take_turns(play, env);
			
			Pair mv = who.take_action( b, game.ep_boards, mode );
			
			// Print for Debug 
			std::cout << who.get_piece() << "'s turn.\t";
	 		std::cout << "Move from (" << mv.prev / 6 << ", " << mv.prev % 6 << ") to (" 
		 	<< mv.next / 6 << ", " << mv.next % 6 << ")\n";
			
			// end game
			if (mv == Pair{} || game.step() > episode::game_threshold)
				break;
			game.record_action(mv, b, who.get_piece());
			train_set_game.record_train_board(b, who.get_piece());
			
			std::cout << b << '\n';
		}

		// check draw game
		if ( game.check_draw(b) ) {
			train_set_game.train_close_episode(new agent());
			stat.close_episode("end", new agent(), b);
		}	
		else {
			agent &win = game.get_winner(env, play, b);
			// winner agent
			std::cout << win.name() << " Wins\n\n";	
			train_set_game.train_close_episode( &win );
			stat.close_episode("end", &win, b);
		}
	}
	return 0;
}
