#include <SDL.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <SDL_ttf.h>
#include <SDL_image.h>
using namespace std;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	bool isRunning = true;

	int movement = 0;
	enum Directions { UP, DOWN, LEFT, RIGHT };
	SDL_Rect snakehead{ 250, 250, 10, 10 };
	deque <SDL_Rect> body;
	int snakesize = 1;
	vector <SDL_Rect> apples;
	SDL_Rect wall1{ 0, 0, 10, 500 };
	SDL_Rect wall2{ 0, 0, 500, 10 };
	SDL_Rect wall3{ 490, 0, 10, 500 };
	SDL_Rect wall4{ 0, 490, 500, 10 };

	for (int i = 0; i < 100; i++) {
		apples.emplace_back(rand() % 100 * 10, rand() % 100 * 10, 10, 10);
	}



	while (isRunning) {
		SDL_Event game;

		while (SDL_PollEvent(&game)) {
			if (game.type == SDL_QUIT) isRunning = false;
			if (game.type == SDL_KEYDOWN) {
				if (game.key.keysym.sym == SDLK_w) movement = UP;
				if (game.key.keysym.sym == SDLK_a) movement = LEFT;
				if (game.key.keysym.sym == SDLK_s) movement = DOWN;
				if (game.key.keysym.sym == SDLK_d) movement = RIGHT;
			}
		}

		switch (movement) {
		case UP:
			snakehead.y -= 10;
			break;
		case LEFT:
			snakehead.x -= 10;
			break;
		case DOWN:
			snakehead.y += 10;
			break;
		case RIGHT:
			snakehead.x += 10;
			break;
		}

		for_each(apples.begin(), apples.end(), [&](auto& eat) {
			if (snakehead.x == eat.x && snakehead.y == eat.y) {
				snakesize += 1;
				eat.x = rand() % 100 * 10;
				eat.y = rand() % 100 * 10;
			}

			});

		for_each(body.begin(), body.end(), [&](auto& snakebody) {
			if (snakehead.x == snakebody.x && snakehead.y == snakebody.y) {
				snakesize = 1;
			}

			});

		body.push_front(snakehead);

		while (body.size() > snakesize) body.pop_back();

		SDL_SetRenderDrawColor(renderer, 150, 100, 45, 255);

		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 190, 230, 40, 255);
		for_each(body.begin(), body.end(), [&](auto& snakebody) {
			SDL_RenderFillRect(renderer, &snakebody);
			});

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		for_each(apples.begin(), apples.end(), [&](auto& appleeaten) {
			SDL_RenderFillRect(renderer, &appleeaten);
			});

		// wall and collision


		SDL_SetRenderDrawColor(renderer, 0, 230, 122, 255);
		SDL_RenderFillRect(renderer, &wall1);


		SDL_SetRenderDrawColor(renderer, 0, 230, 122, 255);
		SDL_RenderFillRect(renderer, &wall2);


		SDL_SetRenderDrawColor(renderer, 0, 230, 122, 255);
		SDL_RenderFillRect(renderer, &wall3);


		SDL_SetRenderDrawColor(renderer, 0, 230, 122, 255);
		SDL_RenderFillRect(renderer, &wall4);




		SDL_RenderPresent(renderer);

		SDL_Delay(60);


	}
	return 0;
}