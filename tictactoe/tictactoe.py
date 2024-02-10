"""
Tic Tac Toe Player
"""

import math

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    x_count = sum(row.count(X) for row in board)
    o_count = sum(row.count(O) for row in board)

    return X if x_count == o_count else O



def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    possible_actions = set()
    for i in range(3):
        for j in range(3):
            if board[i][j] is EMPTY:
                possible_actions.add((i, j))
    return possible_actions



def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    if action not in actions(board):
        raise ValueError("Invalid action")

    new_board = [row.copy() for row in board]
    new_board[action[0]][action[1]] = player(board)
    return new_board



def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    for player in [X, O]:
        # Check rows
        for i in range(3):
            if board[i] == [player] * 3:
                return player

        # Check columns
        for j in range(3):
            if [board[i][j] for i in range(3)] == [player] * 3:
                return player

        # Check diagonals
        if [board[i][i] for i in range(3)] == [player] * 3 or [board[i][2 - i] for i in range(3)] == [player] * 3:
            return player

    return None



def terminal(board):

    """
    Returns True if game is over, False otherwise.
    """
    return winner(board) is not None or all(board[i][j] is not EMPTY for i in range(3) for j in range(3))



def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    winner_player = winner(board)
    if winner_player == X:
        return 1
    elif winner_player == O:
        return -1
    else:
        return 0



def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    if terminal(board):
        return None

    current_player = player(board)

    if current_player == X:
        value, action = max_value(board)
    else:
        value, action = min_value(board)

    return action

def max_value(board):
    if terminal(board):
        return utility(board), None

    value = float("-inf")
    best_action = None

    for action in actions(board):
        new_board = result(board, action)
        min_val, _ = min_value(new_board)

        if min_val > value:
            value = min_val
            best_action = action

    return value, best_action

def min_value(board):
    if terminal(board):
        return utility(board), None

    value = float("inf")
    best_action = None

    for action in actions(board):
        new_board = result(board, action)
        max_val, _ = max_value(new_board)

        if max_val < value:
            value = max_val
            best_action = action

    return value, best_action
