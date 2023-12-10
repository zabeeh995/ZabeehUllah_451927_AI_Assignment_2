#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

#define BOARD_SIZE 3

struct Node {
    Node *parent;
    int board[BOARD_SIZE][BOARD_SIZE];
    int x, y, cost, level;
};

void printMatrix(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

Node *newNode(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int newX, int newY, int level, Node *parent) {
    Node *node = new Node{parent};
    copy(&board[0][0], &board[0][0] + BOARD_SIZE * BOARD_SIZE, &node->board[0][0]);
    swap(node->board[x][y], node->board[newX][newY]);
    node->x = newX;
    node->y = newY;
    node->cost = INT_MAX;
    node->level = level;
    return node;
}

int calculateHeuristic(int board[BOARD_SIZE][BOARD_SIZE], int goal[BOARD_SIZE][BOARD_SIZE]) {
    int heuristic = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != 0) {
                int goalX = (board[i][j] - 1) / BOARD_SIZE;
                int goalY = (board[i][j] - 1) % BOARD_SIZE;
                heuristic += abs(i - goalX) + abs(j - goalY);
            }
        }
    }
    return heuristic;
}

struct comp {
    bool operator()(const Node *lhs, const Node *rhs) const {
        return lhs->cost > rhs->cost;
    }
};

void solve(int initial[BOARD_SIZE][BOARD_SIZE], int x, int y, int goal[BOARD_SIZE][BOARD_SIZE]) {
    priority_queue<Node *, vector<Node *>, comp> pq;

    Node *root = newNode(initial, x, y, x, y, 0, nullptr);
    root->cost = calculateHeuristic(initial, goal);
    pq.push(root);

    while (!pq.empty()) {
        Node *min = pq.top();
        pq.pop();

        if (min->cost == 0) {
            printMatrix(min->board);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = min->x + (i == 0) - (i == 2);
            int newY = min->y + (i == 1) - (i == 3);
            if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE) {
                Node *child = newNode(min->board, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateHeuristic(child->board, goal);
                pq.push(child);
            }
        }
    }
}

int main() {
    int initial[BOARD_SIZE][BOARD_SIZE] = { {1, 2, 3}, {5, 6, 0}, {7, 8, 4} };
    int goal[BOARD_SIZE][BOARD_SIZE] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8} };
    solve(initial, 1, 2, goal);
    return 0;
}
