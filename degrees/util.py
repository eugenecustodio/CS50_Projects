from queue import Queue
class Node:
    def __init__(self, state, action, parent):
        self.state = state
        self.action = action
        self.parent = parent


class StackFrontier():
    def __init__(self):
        self.frontier = []

    def add(self, node):
        self.frontier.append(node)

    def contains_state(self, state):
        return any(node.state == state for node in self.frontier)

    def empty(self):
        return len(self.frontier) == 0

    def remove(self):
        if self.empty():
            raise Exception("empty frontier")
        else:
            node = self.frontier[-1]
            self.frontier = self.frontier[:-1]
            return node


class QueueFrontier():
    def __init__(self):
        self.frontier = Queue()

    def add(self, node):
        self.frontier.put(node)

    def contains_state(self, state):
        return any(node.state == state for node in self.frontier.queue)

    def empty(self):
        return self.frontier.empty()

    def remove(self):
        if self.empty():
            raise Exception("empty frontier")
        else:
            return self.frontier.get()
