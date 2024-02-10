import csv
import sys
import random
import time

# Number of simulations to run
N = 1000

def main():
    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # Read teams into memory from file
    teams = read_teams(sys.argv[1])

    # Simulate N tournaments and keep track of win counts
    counts = simulate_tournaments(teams, N)

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda x: counts[x], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")

def read_teams(filename):
    """Read teams from a CSV file and return a list of team dictionaries."""
    teams = []
    with open(filename, "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            team = {
                "team": row["team"],
                "rating": int(row["rating"])
            }
            teams.append(team)
    return teams

def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability

def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])
    return winners

def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    while len(teams) > 1:
        teams = simulate_round(teams)
    return teams[0]["team"]

def simulate_tournaments(teams, num_simulations):
    """Simulate multiple tournaments and keep track of win counts for each team."""
    counts = {}
    for _ in range(num_simulations):
        winner = simulate_tournament(teams)
        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1
    return counts

if __name__ == "__main__":
    start_time = time.time()
    main()
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Elapsed time: {elapsed_time:.3f} seconds")
