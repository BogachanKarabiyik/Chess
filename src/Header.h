#pragma once

class game {
private:

public:
	std::string array[128] = {};
	int pawn[8] = { 96,98,100,102,104,106,108,110 };
	int rook[2] = { 112, 126 };
	int knight[2] = { 114, 124 };
	int bishop[2] = { 116, 122 };
	int queen = 118;
	int king = 120;

	void fill_array() {
		for (int i = 0; i < 128; i++) {
			array[i] = { ' ' };
		}
	}

	void fill_pions() {
		for (int x = 0; x < 8; x++) {
			array[pawn[x]] = "\033[30mP\033[0m";
			array[pawn[x] + 1] = "\033[30m.\033[0m";
		}
		for (int y = 0; y < 2; y++) {
			array[rook[y]] = "\033[30mR\033[0m";
			array[rook[y] + 1] = "\033[30m.\033[0m";

			array[knight[y]] = "\033[30mN\033[0m";
			array[knight[y] + 1] = "\033[30m.\033[0m";

			array[bishop[y]] = "\033[30mB\033[0m";
			array[bishop[y] + 1] = "\033[30m.\033[0m";
		}
		array[queen] = "\033[30mQ\033[0m";
		array[queen + 1] = "\033[30m.\033[0m";

		array[king] = "\033[30mK\033[0m";
		array[king + 1] = "\033[30m.\033[0m";
	}

}game;

class display {
private:
	int board_number = 7;
public:
	void board(std::string msg) {
		board_number = 7;
		int row_y = 0;
		system("CLS");
		std::cout << "\n                +----------------+\n              8 |";
		for (int i = 0; i < 128; i++) {
			if (i % 16 == 0 && i != 0) {
				std::cout << "\033[0m";
				std::cout << "|\n              " << std::to_string(board_number) << " |";
				row_y++;
				board_number--;
			}
			if ((i/2) % 2 == 0 && row_y % 2 == 0 ) {
				std::cout << "\033[0m";
				std::cout << "\033[47m";
			}
			else if ((i / 2) % 2 != 0 && row_y % 2 != 0) {
				std::cout << "\033[0m";
				std::cout << "\033[47m";
			}
			else {
				std::cout << "\033[0m";
				std::cout << "\033[46m";
			}
			std::cout << game.array[i];
		}
		std::cout << "\033[0m";
		std::cout << "|\n                +----------------+";
		std::cout << "\n                 A B C D E F G H\n";
		std::cout << msg;
	}
}display;

class init {
private:
	int move = 103;
	std::string input = "";
public:
	void play() {
		game.fill_array();
		game.fill_pions();
		while (true) {
			for (int i = 1; i < 128; i++) {
				if (move == i) {
					game.array[i] = "\033[30m*\033[0m";
				}
			}
			std::string msg = "       Move using arrow keys then hit enter";
			display.board(msg);
			game.fill_array();
			game.fill_pions();
			system("pause>0");
			if (GetKeyState('Q') & 0x8000)
			{
				return;
			}
			if (GetKeyState(VK_UP) & 0x8000 && move - 16 >= 1)
			{
				move -= 16;
			}
			else if (GetKeyState(VK_DOWN) & 0x8000 && move + 16 <= 127)
			{
				move += 16;
			}
			else if (GetKeyState(VK_LEFT) & 0x8000 && move - 2 >= 1)
			{
				move -= 2;
			}
			else if (GetKeyState(VK_RIGHT) & 0x8000 && move + 2 <= 127)
			{
				move += 2;
			}
			else if (GetKeyState(VK_RETURN) & 0x8000) {
				for (int x = 0; x < 8; x++) {
					if (move == game.pawn[x] + 1) {
						bool pawn1 = false;
						bool rook = false;
						bool king = false;
						bool pawn2 = false;
						while (true) {
							if (move >= 17) {
								for (int xx = 0; xx < 8; xx++) {
									if (xx == 0 || xx == 1) {
										if (game.rook[xx] != move - 17 && game.knight[xx] != move - 17 && game.bishop[xx] != move - 17) {
											rook = true;
										}
									}
									if (game.pawn[xx] != move - 17) {
										pawn1 = true;
									}
								}
								if (game.king != move - 17 && game.queen != move - 17) {
									king = true;
								}
								if (king && rook && pawn1) {
									game.array[move - 17] = "\033[30m1\033[0m";
								}
							}
							else {
								break;
							}
							if (!king || !rook || !pawn1) {
								break;
							}
							if (move == 97 || move == 99 || move == 101 || move == 103 || move == 105 || move == 107 || move == 109 || move == 111) {
								for (int xx = 0; xx < 8; xx++) {
									if (xx == 0 || xx == 1) {
										if (game.rook[xx] != move - 33 && game.knight[xx] != move - 33 && game.bishop[xx] != move - 33) {
											rook = true;
										}
									}
									if (game.pawn[xx] != move - 33) {
										pawn2 = true;
									}
								}
								if (game.king != move - 33 && game.queen != move - 33) {
									king = true;
								}
								if (king && rook && pawn2) {
									game.array[move - 33] = "\033[30m2\033[0m";
								}
							}
							std::string msg = "       Write the number for the destination";
							display.board(msg);
							std::cout << "\n          > ";
							getline(std::cin, input);
							if (input == "1" && pawn1 && king && rook) {
								game.pawn[x] -= 16;
								game.fill_array();
								game.fill_pions();
								break;
							}
							else if (input == "2" && pawn2 && king && rook) {
								game.pawn[x] -= 32;
								game.fill_array();
								game.fill_pions();
								break;
							}
						}
					}
				}
				for (int y = 0; y < 2; y++) {
					if (move == game.rook[y] + 1) {
						int counter = 0;
						int counter_down = 0;
						int counter_left = 0;
						int counter_left_number = 0;
						int counter_left_number2 = 0;
						int counter_right = 0;
						int counter_right_number = 0;
						int counter_right_number2 = 0;
						bool bool_while = true;
						bool rook = false;
						bool pawn = false;
						bool king = false;
						while (bool_while) {
							if (counter == 0) {
								for (int z = (move - 17); z >= 0; z -= 16) {
									for (int xx = 0; xx < 8; xx++) {
										if (game.pawn[xx] != z) {
											pawn = true;
										}
										else {
											pawn = false;
											xx = 8;
										}
									}
									for (int yy = 0; yy < 2; yy++) {
										if (game.rook[yy] != z && game.knight[yy] != z && game.bishop[yy] != z) {
											rook = true;
										}
										else {
											rook = false;
											yy = 2;
										}
									}
									if (game.king != z && game.queen != z) {
										king = true;
									}
									else {
										king = false;
									}
									if (king && rook && pawn) {
										counter++;
										game.array[z] = "\033[30m" + std::to_string(counter) + "\033[0m";
										game.array[z + 1] = "\033[30m.\033[0m";
									}
									else {
										z = -1;
									}
								}
								counter_down = counter;
								for (int k = (move + 15); k <= 127; k += 16) {
									for (int xx = 0; xx < 8; xx++) {
										if (game.pawn[xx] != k) {
											pawn = true;
										}
										else {
											pawn = false;
											xx = 8;
										}
									}
									for (int yy = 0; yy < 2; yy++) {
										if (game.rook[yy] != k && game.knight[yy] != k && game.bishop[yy] != k) {
											rook = true;
										}
										else {
											rook = false;
											yy = 2;
										}
									}
									if (game.king != k && game.queen != k) {
										king = true;
									}
									else {
										king = false;
									}
									if (king && rook && pawn) {
										counter_down++;
										game.array[k] = "\033[30m" + std::to_string(counter_down) + "\033[0m";
										game.array[k + 1] = "\033[30m.\033[0m";
									}
									else {
										k = 128;
									}
								}
								counter_left = counter_down;
								for (int u = (move - 3); u >= move - (move % 16); u -= 2) {
									for (int xx = 0; xx < 8; xx++) {
										if (game.pawn[xx] != u) {
											pawn = true;
										}
										else {
											pawn = false;
											xx = 8;
										}
									}
									for (int yy = 0; yy < 2; yy++) {
										if (game.rook[yy] != u && game.knight[yy] != u && game.bishop[yy] != u) {
											rook = true;
										}
										else {
											rook = false;
											yy = 2;
										}
									}
									if (game.king != u && game.queen != u) {
										king = true;
									}
									else {
										king = false;
									}
									if (king && rook && pawn) {
										counter_left++;
										if (counter_left >= 10) {
											counter_left_number = counter_left / 10;
											counter_left_number2 = counter_left_number * 10;
											game.array[u] = "\033[30m" + std::to_string(counter_left_number) + "\033[0m";
											game.array[u + 1] = "\033[30m" + std::to_string(counter_left - counter_left_number2) + "\033[0m";
										}
										else {
											game.array[u] = "\033[30m" + std::to_string(counter_left) + "\033[0m";
											game.array[u + 1] = "\033[30m.\033[0m";
										}
									}
									else {
										u = -1;
									}
								}
								counter_right = counter_left;
								int eq = ((move / 16) * 16) + 15;
								for (int h = (move + 1); h <= eq; h += 2) {
									for (int xx = 0; xx < 8; xx++) {
										if (game.pawn[xx] != h) {
											pawn = true;
										}
										else {
											pawn = false;
											xx = 8;
										}
									}
									for (int yy = 0; yy < 2; yy++) {
										if (game.rook[yy] != h && game.knight[yy] != h && game.bishop[yy] != h) {
											rook = true;
										}
										else {
											rook = false;
											yy = 2;
										}
									}
									if (game.king != h && game.queen != h) {
										king = true;
									}
									else {
										king = false;
									}
									if (king && rook && pawn) {
										counter_right++;
										if (counter_right >= 10) {
											counter_right_number = counter_right / 10;
											counter_right_number2 = counter_right_number * 10;
											game.array[h] = "\033[30m" + std::to_string(counter_right_number) + "\033[0m";
											game.array[h + 1] = "\033[30m" + std::to_string(counter_right - counter_right_number2) + "\033[0m";
										}
										else {
											game.array[h] = "\033[30m" + std::to_string(counter_right) + "\033[0m";
											game.array[h + 1] = "\033[30m.\033[0m";
										}
									}
									else {
										h = 129;
									}
								}
							}
							std::string msg = "       Write the number for the destination";
							display.board(msg);
							std::cout << "\n          > ";
							getline(std::cin, input);
							for (int j = 1; j <= counter; j++) {
								if (input == std::to_string(j)) {
									game.rook[y] -= (j * 16);
									game.fill_array();
									game.fill_pions();
									j = 130;
									bool_while = false;
								}
							}
							for (int p = (counter + 1) ; p <= counter_down; p++) {
								if (input == std::to_string(p)) {
									game.rook[y] += ((p - counter) * 16);
									game.fill_array();
									game.fill_pions();
									p = 130;
									bool_while = false;
								}
							}
							for (int m = (counter_down + 1); m <= counter_left; m++) {
								if (input == std::to_string(m)) {
									game.rook[y] -= (m - counter_down) * 2;
									game.fill_array();
									game.fill_pions();
									m = 130;
									bool_while = false;
								}
							}
							for (int v = (counter_left + 1); v <= counter_right; v++) {
								if (input == std::to_string(v)) {
									game.rook[y] += (v - counter_left) * 2;
									game.fill_array();
									game.fill_pions();
									v = 130;
									bool_while = false;
								}
							}
							if (counter == 0 && counter_down == 0 && counter_left == 0 && counter_right == 0) {
								bool_while = false;
							}
						}
					}
					else if (move == game.knight[y] + 1) {
						bool while_bool = true;
						int counter = 0;
						bool knight1 = false;
						bool knight2 = false;
						bool knight3 = false;
						bool knight4 = false;
						bool knight5 = false;
						bool knight6 = false;
						bool knight7 = false;
						bool knight8 = false;
						bool pawn = false;
						bool rook = false;
						bool king = false;
						while (while_bool) {
							if (counter == 0) {
								for (int z = 0; z < 8; z++) {
									counter++;
									if (move - 35 >= 0 && z == 0 && (move - 1) % 16 != 0) {
										for (int xx = 0; xx < 8; xx++) {
											if (game.pawn[xx] != move - 35) {
												pawn = true;
											}
											else {
												pawn = false;
												xx = 8;
											}
										}
										for (int yy = 0; yy < 2; yy++) {
											if (game.rook[yy] != move - 35 && game.knight[yy] != move - 35 && game.bishop[yy] != move - 35) {
												rook = true;
											}
											else {
												rook = false;
												yy = 2;
											}
										}
										if (game.king != move - 35 && game.queen != move - 35) {
											king = true;
										}
										else {
											king = false;
										}
										if (pawn && rook && king) {
											game.array[move - 35] = "\033[30m" + std::to_string(counter) + "\033[0m";
											game.array[move - 34] = "\033[30m.\033[0m";
											knight1 = true;
										}
									}
									else if (move - 31 >= 0 && z == 1 && (move + 1) % 16 != 0) {
										for (int xx = 0; xx < 8; xx++) {
											if (game.pawn[xx] != move - 31) {
												pawn = true;
											}
											else {
												pawn = false;
												xx = 8;
											}
										}
										for (int yy = 0; yy < 2; yy++) {
											if (game.rook[yy] != move - 31 && game.knight[yy] != move - 31 && game.bishop[yy] != move - 31) {
												rook = true;
											}
											else {
												rook = false;
												yy = 2;
											}
										}
										if (game.king != move - 31 && game.queen != move - 31) {
											king = true;
										}
										else {
											king = false;
										}
										if (pawn && rook && king) {
											game.array[move - 31] = "\033[30m" + std::to_string(counter) + "\033[0m";
											game.array[move - 30] = "\033[30m.\033[0m";
											knight2 = true;
										}
									}
									else if (move - 13 >= 0 && z == 2 && (move + 1) % 16 != 0 && (move + 3) % 16 != 0) {
										for (int xx = 0; xx < 8; xx++) {
											if (game.pawn[xx] != move - 13) {
												pawn = true;
											}
											else {
												pawn = false;
												xx = 8;
											}
										}
										for (int yy = 0; yy < 2; yy++) {
											if (game.rook[yy] != move - 13 && game.knight[yy] != move - 13 && game.bishop[yy] != move - 13) {
												rook = true;
											}
											else {
												rook = false;
												yy = 2;
											}
										}
										if (game.king != move - 13 && game.queen != move - 13) {
											king = true;
										}
										else {
											king = false;
										}
										if (pawn && rook && king) {
											game.array[move - 13] = "\033[30m" + std::to_string(counter) + "\033[0m";
											game.array[move - 12] = "\033[30m.\033[0m";
											knight3 = true;
										}
									}
									else if (move + 19 <= 127 && z == 3 && (move + 1) % 16 != 0 && (move + 3) % 16 != 0) {
										for (int xx = 0; xx < 8; xx++) {
											if (game.pawn[xx] != move + 19) {
												pawn = true;
											}
											else {
												pawn = false;
												xx = 8;
											}
										}
										for (int yy = 0; yy < 2; yy++) {
											if (game.rook[yy] != move + 19 && game.knight[yy] != move + 19 && game.bishop[yy] != move + 19) {
												rook = true;
											}
											else {
												rook = false;
												yy = 2;
											}
										}
										if (game.king != move + 19 && game.queen != move + 19) {
											king = true;
										}
										else {
											king = false;
										}
										if (pawn && rook && king) {
											game.array[move + 19] = "\033[30m" + std::to_string(counter) + "\033[0m";
											game.array[move + 20] = "\033[30m.\033[0m";
											knight4 = true;
										}
									}
									else if (move + 33 <= 127 && z == 4 && (move + 1) % 16 != 0) {
									for (int xx = 0; xx < 8; xx++) {
										if (game.pawn[xx] != move + 33) {
											pawn = true;
										}
										else {
											pawn = false;
											xx = 8;
										}
									}
									for (int yy = 0; yy < 2; yy++) {
										if (game.rook[yy] != move + 33 && game.knight[yy] != move + 33 && game.bishop[yy] != move + 33) {
											rook = true;
										}
										else {
											rook = false;
											yy = 2;
										}
									}
									if (game.king != move + 33 && game.queen != move + 33) {
										king = true;
									}
									else {
										king = false;
									}
									if (pawn && rook && king) {
										game.array[move + 33] = "\033[30m" + std::to_string(counter) + "\033[0m";
										game.array[move + 34] = "\033[30m.\033[0m";
										knight5 = true;
									}
									}
									else if (move + 29 <= 127 && z == 5 && (move - 1) % 16 != 0) {
									for (int xx = 0; xx < 8; xx++) {
										if (game.pawn[xx] != move + 29) {
											pawn = true;
										}
										else {
											pawn = false;
											xx = 8;
										}
									}
									for (int yy = 0; yy < 2; yy++) {
										if (game.rook[yy] != move + 29 && game.knight[yy] != move + 29 && game.bishop[yy] != move + 29) {
											rook = true;
										}
										else {
											rook = false;
											yy = 2;
										}
									}
									if (game.king != move + 29 && game.queen != move + 29) {
										king = true;
									}
									else {
										king = false;
									}
									if (pawn && rook && king) {
										game.array[move + 29] = "\033[30m" + std::to_string(counter) + "\033[0m";
										game.array[move + 30] = "\033[30m.\033[0m";
										knight6 = true;
									}
									}
									else if (move + 11 <= 127 && z == 6 && (move - 1) % 16 != 0 && (move - 3) % 16 != 0) {
									for (int xx = 0; xx < 8; xx++) {
										if (game.pawn[xx] != move + 11) {
											pawn = true;
										}
										else {
											pawn = false;
											xx = 8;
										}
									}
									for (int yy = 0; yy < 2; yy++) {
										if (game.rook[yy] != move + 11 && game.knight[yy] != move + 11 && game.bishop[yy] != move + 11) {
											rook = true;
										}
										else {
											rook = false;
											yy = 2;
										}
									}
									if (game.king != move + 11 && game.queen != move + 11) {
										king = true;
									}
									else {
										king = false;
									}
									if (pawn && rook && king) {
										game.array[move + 11] = "\033[30m" + std::to_string(counter) + "\033[0m";
										game.array[move + 12] = "\033[30m.\033[0m";
										knight7 = true;
									}
									}
									else if (move - 21 >= 0 && z == 7 && (move - 1) % 16 != 0 && (move - 3) % 16 != 0) {
									for (int xx = 0; xx < 8; xx++) {
										if (game.pawn[xx] != move - 21) {
											pawn = true;
										}
										else {
											pawn = false;
											xx = 8;
										}
									}
									for (int yy = 0; yy < 2; yy++) {
										if (game.rook[yy] != move - 21 && game.knight[yy] != move - 21 && game.bishop[yy] != move - 21) {
											rook = true;
										}
										else {
											rook = false;
											yy = 2;
										}
									}
									if (game.king != move - 21 && game.queen != move - 21) {
										king = true;
									}
									else {
										king = false;
									}
									if (pawn && rook && king) {
										game.array[move - 21] = "\033[30m" + std::to_string(counter) + "\033[0m";
										game.array[move - 20] = "\033[30m.\033[0m";
										knight8 = true;
									}
									}
								}
							}
							std::string msg = "       Write the number for the destination";
							display.board(msg);
							std::cout << "\n          > ";
							getline(std::cin, input);
							if (input == "1" && knight1 == true) {
								game.knight[y] -= 34;
								game.fill_array();
								game.fill_pions();
								break;
							}
							else if (input == "2" && knight2 == true) {
								game.knight[y] -= 30;
								game.fill_array();
								game.fill_pions();
								break;
							}
							else if (input == "3" && knight3 == true) {
								game.knight[y] -= 12;
								game.fill_array();
								game.fill_pions();
								break;
							}
							else if (input == "4" && knight4 == true) {
								game.knight[y] += 20;
								game.fill_array();
								game.fill_pions();
								break;
							}
							else if (input == "5" && knight5 == true) {
								game.knight[y] += 34;
								game.fill_array();
								game.fill_pions();
								break;
							}
							else if (input == "6" && knight6 == true) {
								game.knight[y] += 30;
								game.fill_array();
								game.fill_pions();
								break;
							}
							else if (input == "7" && knight7 == true) {
								game.knight[y] += 12;
								game.fill_array();
								game.fill_pions();
								break;
							}
							else if (input == "8" && knight8 == true) {
								game.knight[y] -= 20;
								game.fill_array();
								game.fill_pions();
								break;
							}
							if (!knight1 && !knight2 && !knight3 && !knight4 && !knight5 && !knight6 && !knight7 && !knight8) {
								break;
							}
						}
					}
					else if (move == game.bishop[y] + 1) {
					int counter = 0;
					int counter_down = 0;
					int counter_left = 0;
					int counter_left_number = 0;
					int counter_left_number2 = 0;
					int counter_right = 0;
					int counter_right_number = 0;
					int counter_right_number2 = 0;
					bool bool_while = true;
					bool pawn = false;
					bool rook = false;
					bool king = false;
					while (bool_while) {
						if (counter == 0) {
							for (int z = (move - 19); z >= 0; z -= 18) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != z) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != z && game.knight[yy] != z && game.bishop[yy] != z) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != z && game.queen != z) {
									king = true;
								}
								else {
									king = false;
								}
								if (king && rook && pawn) {
									if ((z + 18) % 16 != 0) {
										counter++;
										game.array[z] = "\033[30m" + std::to_string(counter) + "\033[0m";
										game.array[z + 1] = "\033[30m.\033[0m";
									}
									else {
										z = -1;
									}
								}
								else {
									z = -1;
								}
							}
							counter_down = counter;
							for (int k = (move + 17); k <= 127; k += 18) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != k) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != k && game.knight[yy] != k && game.bishop[yy] != k) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != k && game.queen != k) {
									king = true;
								}
								else {
									king = false;
								}
								if (king && rook && pawn) {
									if (k % 16 != 0) {
										counter_down++;
										game.array[k] = "\033[30m" + std::to_string(counter_down) + "\033[0m";
										game.array[k + 1] = "\033[30m.\033[0m";
									}
									else {
										k = 128;
									}
								}
								else {
									k = 128;
								}
							}
							counter_left = counter_down;
							for (int u = (move + 13); u <= 127; u += 14) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != u) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != u && game.knight[yy] != u && game.bishop[yy] != u) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != u && game.queen != u) {
									king = true;
								}
								else {
									king = false;
								}
								if (king && rook && pawn) {
									if ((u - 14) % 16 != 0) {
										counter_left++;
										if (counter_left >= 10) {
											counter_left_number = counter_left / 10;
											counter_left_number2 = counter_left_number * 10;
											game.array[u] = "\033[30m" + std::to_string(counter_left_number) + "\033[0m";
											game.array[u + 1] = "\033[30m" + std::to_string(counter_left - counter_left_number2) + "\033[0m";
										}
										else {
											game.array[u] = "\033[30m" + std::to_string(counter_left) + "\033[0m";
											game.array[u + 1] = "\033[30m.\033[0m";
										}
									}
									else {
										u = 128;
									}
								}
								else {
									u = 128;
								}
							}
							counter_right = counter_left;
							for (int h = (move - 15); h >= 0; h -= 14) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != h) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != h && game.knight[yy] != h && game.bishop[yy] != h) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != h && game.queen != h) {
									king = true;
								}
								else {
									king = false;
								}
								if (king && rook && pawn) {
									if (h % 16 != 0) {
										counter_right++;
										if (counter_right >= 10) {
											counter_right_number = counter_right / 10;
											counter_right_number2 = counter_right_number * 10;
											game.array[h] = "\033[30m" + std::to_string(counter_right_number) + "\033[0m";
											game.array[h + 1] = "\033[30m" + std::to_string(counter_right - counter_right_number2) + "\033[0m";
										}
										else {
											game.array[h] = "\033[30m" + std::to_string(counter_right) + "\033[0m";
											game.array[h + 1] = "\033[30m.\033[0m";
										}
									}
									else {
										h = -1;
									}
								}
								else {
									h = -1;
								}
							}
						}
						std::string msg = "       Write the number for the destination";
						display.board(msg);
						std::cout << "\n          > ";
						getline(std::cin, input);
						for (int j = 1; j <= counter; j++) {
							if (input == std::to_string(j)) {
								game.bishop[y] -= ((j * 16) + (j * 2));
								game.fill_array();
								game.fill_pions();
								j = 130;
								bool_while = false;
							}
						}
						for (int p = (counter + 1); p <= counter_down; p++) {
							if (input == std::to_string(p)) {
								game.bishop[y] += ((p - counter) * 16) + ((p - counter) * 2);
								game.fill_array();
								game.fill_pions();
								p = 130;
								bool_while = false;
							}
						}
						for (int m = (counter_down + 1); m <= counter_left; m++) {
							if (input == std::to_string(m)) {
								game.bishop[y] += ((m - counter_down) * 16) - ((m - counter_down) * 2);
								game.fill_array();
								game.fill_pions();
								m = 130;
								bool_while = false;
							}
						}
						for (int v = (counter_left + 1); v <= counter_right; v++) {
							if (input == std::to_string(v)) {
								game.bishop[y] -= ((v - counter_left) * 16) - ((v - counter_left) * 2);
								game.fill_array();
								game.fill_pions();
								v = 130;
								bool_while = false;
							}
						}
						if (counter == 0 && counter_down == 0 && counter_left == 0 && counter_right == 0) {
							bool_while = false;
						}
					}
					}
				}
				if (move == game.queen + 1) {
					int counter = 0;
					int counter_down = 0;
					int counter_left = 0;
					int counter_left_number = 0;
					int counter_left_number2 = 0;
					int counter_right = 0;
					int counter_right_number = 0;
					int counter_right_number2 = 0;

					int counter_ = 0;
					int counter_number = 0;
					int counter_number2 = 0;
					int counter_down_ = 0;
					int counter_down_number = 0;
					int counter_down_number2 = 0;
					int counter_left_ = 0;
					int counter_left_number_ = 0;
					int counter_left_number2_ = 0;
					int counter_right_ = 0;
					int counter_right_number_ = 0;
					int counter_right_number2_ = 0;
					bool bool_while = true;
					bool pawn = false;
					bool rook = false;
					bool king = false;
					while (bool_while) {
						if (counter == 0) {
							for (int z = (move - 19); z >= 0; z -= 18) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != z) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != z && game.knight[yy] != z && game.bishop[yy] != z) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != z && game.queen != z) {
									king = true;
								}
								else {
									king = false;
								}
								if (king && rook && pawn) {
									if ((z + 18) % 16 != 0) {
										counter++;
										game.array[z] = "\033[30m" + std::to_string(counter) + "\033[0m";
										game.array[z + 1] = "\033[30m.\033[0m";
									}
									else {
										z = -1;
									}
								}
								else {
									z = -1;
								}
							}
							counter_down = counter;
							for (int k = (move + 17); k <= 127; k += 18) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != k) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != k && game.knight[yy] != k && game.bishop[yy] != k) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != k && game.queen != k) {
									king = true;
								}
								else {
									king = false;
								}
								if (king && rook && pawn) {
									if (k % 16 != 0) {
										counter_down++;
										game.array[k] = "\033[30m" + std::to_string(counter_down) + "\033[0m";
										game.array[k + 1] = "\033[30m.\033[0m";
									}
									else {
										k = 128;
									}
								}
								else {
									k = 128;
								}
							}
							counter_left = counter_down;
							for (int u = (move + 13); u <= 127; u += 14) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != u) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != u && game.knight[yy] != u && game.bishop[yy] != u) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != u && game.queen != u) {
									king = true;
								}
								else {
									king = false;
								}
								if (king && rook && pawn) {
									if ((u - 14) % 16 != 0) {
										counter_left++;
										if (counter_left >= 10) {
											counter_left_number = counter_left / 10;
											counter_left_number2 = counter_left_number * 10;
											game.array[u] = "\033[30m" + std::to_string(counter_left_number) + "\033[0m";
											game.array[u + 1] = "\033[30m" + std::to_string(counter_left - counter_left_number2) + "\033[0m";
										}
										else {
											game.array[u] = "\033[30m" + std::to_string(counter_left) + "\033[0m";
											game.array[u + 1] = "\033[30m.\033[0m";
										}
									}
									else {
										u = 128;
									}
								}
								else {
									u = 128;
								}
							}
							counter_right = counter_left;
							for (int h = (move - 15); h >= 0; h -= 14) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != h) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != h && game.knight[yy] != h && game.bishop[yy] != h) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != h && game.queen != h) {
									king = true;
								}
								else {
									king = false;
								}
								if (king && rook && pawn) {
									if (h % 16 != 0) {
										counter_right++;
										if (counter_right >= 10) {
											counter_right_number = counter_right / 10;
											counter_right_number2 = counter_right_number * 10;
											game.array[h] = "\033[30m" + std::to_string(counter_right_number) + "\033[0m";
											game.array[h + 1] = "\033[30m" + std::to_string(counter_right - counter_right_number2) + "\033[0m";
										}
										else {
											game.array[h] = "\033[30m" + std::to_string(counter_right) + "\033[0m";
											game.array[h + 1] = "\033[30m.\033[0m";
										}
									}
									else {
										h = -1;
									}
								}
								else {
									h = -1;
								}
							}
							counter_ = counter_right;
							for (int z = (move - 17); z >= 0; z -= 16) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != z) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != z && game.knight[yy] != z && game.bishop[yy] != z) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != z && game.queen != z) {
									king = true;
								}
								else {
									king = false;
								}
								if (king && rook && pawn) {
									counter_++;
									if (counter_ >= 10) {
										counter_number = counter_ / 10;
										counter_number2 = counter_number * 10;
										game.array[z] = "\033[30m" + std::to_string(counter_number) + "\033[0m";
										game.array[z + 1] = "\033[30m" + std::to_string(counter_ - counter_number2) + "\033[0m";
									}
									else {
										game.array[z] = "\033[30m" + std::to_string(counter_) + "\033[0m";
										game.array[z + 1] = "\033[30m.\033[0m";
									}
								}
								else {
									z = -1;
								}
							}
							counter_down_ = counter_;
							for (int k = (move + 15); k <= 127; k += 16) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != k) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != k && game.knight[yy] != k && game.bishop[yy] != k) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != k && game.queen != k) {
									king = true;
								}
								else {
									king = false;
								}
								if (king && rook && pawn) {
									counter_down_++;
									if (counter_down_ >= 10) {
										counter_down_number = counter_down_ / 10;
										counter_down_number2 = counter_down_number * 10;
										game.array[k] = "\033[30m" + std::to_string(counter_down_number) + "\033[0m";
										game.array[k + 1] = "\033[30m" + std::to_string(counter_down_ - counter_down_number2) + "\033[0m";
									}
									else {
										game.array[k] = "\033[30m" + std::to_string(counter_down_) + "\033[0m";
										game.array[k + 1] = "\033[30m.\033[0m";
									}
								}
								else {
									k = 129;
								}
							}
							counter_left_ = counter_down_;
							for (int u = (move - 3); u >= move - (move % 16); u -= 2) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != u) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != u && game.knight[yy] != u && game.bishop[yy] != u) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != u && game.queen != u) {
									king = true;
								}
								else {
									king = false;
								}
								if (king && rook && pawn) {
									counter_left_++;
									if (counter_left_ >= 10) {
										counter_left_number_ = counter_left_ / 10;
										counter_left_number2_ = counter_left_number_ * 10;
										game.array[u] = "\033[30m" + std::to_string(counter_left_number_) + "\033[0m";
										game.array[u + 1] = "\033[30m" + std::to_string(counter_left_ - counter_left_number2_) + "\033[0m";
									}
									else {
										game.array[u] = "\033[30m" + std::to_string(counter_left_) + "\033[0m";
										game.array[u + 1] = "\033[30m.\033[0m";
									}
								}
								else {
									u = -1;
								}
							}
							counter_right_ = counter_left_;
							int eq = ((move / 16) * 16) + 15;
							for (int h = (move + 1); h <= eq; h += 2) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != h) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != h && game.knight[yy] != h && game.bishop[yy] != h) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != h && game.queen != h) {
									king = true;
								}
								else {
									king = false;
								}
								if (king && rook && pawn) {
									counter_right_++;
									if (counter_right_ >= 10) {
										counter_right_number_ = counter_right_ / 10;
										counter_right_number2_ = counter_right_number_ * 10;
										game.array[h] = "\033[30m" + std::to_string(counter_right_number_) + "\033[0m";
										game.array[h + 1] = "\033[30m" + std::to_string(counter_right_ - counter_right_number2_) + "\033[0m";
									}
									else {
										game.array[h] = "\033[30m" + std::to_string(counter_right_) + "\033[0m";
										game.array[h + 1] = "\033[30m.\033[0m";
									}
								}
								else {
									h = 129;
								}
							}
						}
						std::string msg = "       Write the number for the destination";
						display.board(msg);
						std::cout << "\n          > ";
						getline(std::cin, input);
						for (int j = 1; j <= counter; j++) {
							if (input == std::to_string(j)) {
								game.queen -= ((j * 16) + (j * 2));
								game.fill_array();
								game.fill_pions();
								j = 130;
								bool_while = false;
							}
						}
						for (int p = (counter + 1); p <= counter_down; p++) {
							if (input == std::to_string(p)) {
								game.queen += ((p - counter) * 16) + ((p - counter) * 2);
								game.fill_array();
								game.fill_pions();
								p = 130;
								bool_while = false;
							}
						}
						for (int m = (counter_down + 1); m <= counter_left; m++) {
							if (input == std::to_string(m)) {
								game.queen += ((m - counter_down) * 16) - ((m - counter_down) * 2);
								game.fill_array();
								game.fill_pions();
								m = 130;
								bool_while = false;
							}
						}
						for (int v = (counter_left + 1); v <= counter_right; v++) {
							if (input == std::to_string(v)) {
								game.queen -= ((v - counter_left) * 16) - ((v - counter_left) * 2);
								game.fill_array();
								game.fill_pions();
								v = 130;
								bool_while = false;
							}
						}

						for (int j = (counter_right + 1); j <= counter_; j++) {
							if (input == std::to_string(j)) {
								game.queen -= ((j - counter_right) * 16);
								game.fill_array();
								game.fill_pions();
								j = 130;
								bool_while = false;
							}
						}
						for (int p = (counter_ + 1); p <= counter_down_; p++) {
							if (input == std::to_string(p)) {
								game.queen += ((p - counter_) * 16);
								game.fill_array();
								game.fill_pions();
								p = 130;
								bool_while = false;
							}
						}
						for (int m = (counter_down_ + 1); m <= counter_left_; m++) {
							if (input == std::to_string(m)) {
								game.queen -= (m - counter_down_) * 2;
								game.fill_array();
								game.fill_pions();
								m = 130;
								bool_while = false;
							}
						}
						for (int v = (counter_left_ + 1); v <= counter_right_; v++) {
							if (input == std::to_string(v)) {
								game.queen += (v - counter_left_) * 2;
								game.fill_array();
								game.fill_pions();
								v = 130;
								bool_while = false;
							}
						}
						if (counter == 0 && counter_down == 0 && counter_left == 0 && counter_right == 0) {
							bool_while = false;
						}
					}
				}
				else if (move == game.king + 1) {
					bool while_bool = true;
					int counter = 0;
					bool king1 = false;
					bool king2 = false;
					bool king3 = false;
					bool king4 = false;
					bool king5 = false;
					bool king6 = false;
					bool king7 = false;
					bool king8 = false;
					bool pawn = false;
					bool rook = false;
					bool king = false;
					while (while_bool) {
						if (counter == 0) {
							for (int z = 0; z < 8; z++) {
								counter++;
								if (move - 17 >= 0 && z == 0) {
									for (int xx = 0; xx < 8; xx++) {
										if (game.pawn[xx] != move - 17) {
											pawn = true;
										}
										else {
											pawn = false;
											xx = 8;
										}
									}
									for (int yy = 0; yy < 2; yy++) {
										if (game.rook[yy] != move - 17 && game.knight[yy] != move - 17 && game.bishop[yy] != move - 17) {
											rook = true;
										}
										else {
											rook = false;
											yy = 2;
										}
									}
									if (game.king != move - 17 && game.queen != move - 17) {
										king = true;
									}
									else {
										king = false;
									}
									if (pawn && rook && king) {
										game.array[move - 17] = "\033[30m" + std::to_string(counter) + "\033[0m";
										game.array[move - 16] = "\033[30m.\033[0m";
										king1 = true;
									}
								}
								else if (move + 15 <= 127 && z == 1) {
									for (int xx = 0; xx < 8; xx++) {
										if (game.pawn[xx] != move + 15) {
											pawn = true;
										}
										else {
											pawn = false;
											xx = 8;
										}
									}
									for (int yy = 0; yy < 2; yy++) {
										if (game.rook[yy] != move + 15 && game.knight[yy] != move + 15 && game.bishop[yy] != move + 15) {
											rook = true;
										}
										else {
											rook = false;
											yy = 2;
										}
									}
									if (game.king != move + 15 && game.queen != move + 15) {
										king = true;
									}
									else {
										king = false;
									}
									if (pawn && rook && king) {
										game.array[move + 15] = "\033[30m" + std::to_string(counter) + "\033[0m";
										game.array[move + 16] = "\033[30m.\033[0m";
										king2 = true;
									}
								}
								else if (move - 3 >= 0 && z == 2 && (move - 1) % 16 != 0) {
									for (int xx = 0; xx < 8; xx++) {
										if (game.pawn[xx] != move - 3) {
											pawn = true;
										}
										else {
											pawn = false;
											xx = 8;
										}
									}
									for (int yy = 0; yy < 2; yy++) {
										if (game.rook[yy] != move - 3 && game.knight[yy] != move - 3 && game.bishop[yy] != move - 3) {
											rook = true;
										}
										else {
											rook = false;
											yy = 2;
										}
									}
									if (game.king != move - 3 && game.queen != move - 3) {
										king = true;
									}
									else {
										king = false;
									}
									if (pawn && rook && king) {
										game.array[move - 3] = "\033[30m" + std::to_string(counter) + "\033[0m";
										game.array[move - 2] = "\033[30m.\033[0m";
										king3 = true;
									}
								}
								else if (move + 1 <= 127 && z == 3 && (move + 1) % 16 != 0) {
									for (int xx = 0; xx < 8; xx++) {
										if (game.pawn[xx] != move + 1) {
											pawn = true;
										}
										else {
											pawn = false;
											xx = 8;
										}
									}
									for (int yy = 0; yy < 2; yy++) {
										if (game.rook[yy] != move + 1 && game.knight[yy] != move + 1 && game.bishop[yy] != move + 1) {
											rook = true;
										}
										else {
											rook = false;
											yy = 2;
										}
									}
									if (game.king != move + 1 && game.queen != move + 1) {
										king = true;
									}
									else {
										king = false;
									}
									if (pawn && rook && king) {
										game.array[move + 1] = "\033[30m" + std::to_string(counter) + "\033[0m";
										game.array[move + 2] = "\033[30m.\033[0m";
										king4 = true;
									}
								}
								else if (move - 19 >= 0 && z == 4 && (move - 1) % 16 != 0) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != move - 19) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != move - 19 && game.knight[yy] != move - 19 && game.bishop[yy] != move - 19) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != move - 19 && game.queen != move - 19) {
									king = true;
								}
								else {
									king = false;
								}
								if (pawn && rook && king) {
									game.array[move - 19] = "\033[30m" + std::to_string(counter) + "\033[0m";
									game.array[move - 18] = "\033[30m.\033[0m";
									king5 = true;
								}
								}
								else if (move - 15 >= 0 && z == 5 && (move + 1) % 16 != 0) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != move - 15) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != move - 15 && game.knight[yy] != move - 15 && game.bishop[yy] != move - 15) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != move - 15 && game.queen != move - 15) {
									king = true;
								}
								else {
									king = false;
								}
								if (pawn && rook && king) {
									game.array[move - 15] = "\033[30m" + std::to_string(counter) + "\033[0m";
									game.array[move - 14] = "\033[30m.\033[0m";
									king6 = true;
								}
								}
								else if (move + 17 <= 127 && z == 6 && (move + 1) % 16 != 0) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != move + 17) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != move + 17 && game.knight[yy] != move + 17 && game.bishop[yy] != move + 17) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != move + 17 && game.queen != move + 17) {
									king = true;
								}
								else {
									king = false;
								}
								if (pawn && rook && king) {
									game.array[move + 17] = "\033[30m" + std::to_string(counter) + "\033[0m";
									game.array[move + 18] = "\033[30m.\033[0m";
									king7 = true;
								}
								}
								else if (move + 13 <= 127 && z == 7 && (move - 1) % 16 != 0) {
								for (int xx = 0; xx < 8; xx++) {
									if (game.pawn[xx] != move + 13) {
										pawn = true;
									}
									else {
										pawn = false;
										xx = 8;
									}
								}
								for (int yy = 0; yy < 2; yy++) {
									if (game.rook[yy] != move + 13 && game.knight[yy] != move + 13 && game.bishop[yy] != move + 13) {
										rook = true;
									}
									else {
										rook = false;
										yy = 2;
									}
								}
								if (game.king != move + 13 && game.queen != move + 13) {
									king = true;
								}
								else {
									king = false;
								}
								if (pawn && rook && king) {
									game.array[move + 13] = "\033[30m" + std::to_string(counter) + "\033[0m";
									game.array[move + 14] = "\033[30m.\033[0m";
									king8 = true;
								}
								}
							}
						}
						std::string msg = "       Write the number for the destination";
						display.board(msg);
						std::cout << "\n          > ";
						getline(std::cin, input);
						if (input == "1" && king1 == true) {
							game.king -= 16;
							game.fill_array();
							game.fill_pions();
							break;
						}
						else if (input == "2" && king2 == true) {
							game.king += 16;
							game.fill_array();
							game.fill_pions();
							break;
						}
						else if (input == "3" && king3 == true) {
							game.king -= 2;
							game.fill_array();
							game.fill_pions();
							break;
						}
						else if (input == "4" && king4 == true) {
							game.king += 2;
							game.fill_array();
							game.fill_pions();
							break;
						}
						else if (input == "5" && king5 == true) {
							game.king -= 18;
							game.fill_array();
							game.fill_pions();
							break;
						}
						else if (input == "6" && king6 == true) {
							game.king -= 14;
							game.fill_array();
							game.fill_pions();
							break;
						}
						else if (input == "7" && king7 == true) {
							game.king += 18;
							game.fill_array();
							game.fill_pions();
							break;
						}
						else if (input == "8" && king8 == true) {
							game.king += 14;
							game.fill_array();
							game.fill_pions();
							break;
						}
						if (!king1 && !king2 && !king3 && !king4 && !king5 && !king6 && !king7 && !king8) {
							break;
						}
					}
				}
			}
		}
	}
}init;