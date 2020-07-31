#include <bits/stdc++.h>

using namespace std;

template <typename... T>
void read(T&... args) {
	((cin >> args), ...);
}
template <typename... Args>
void write(Args&... args) {
	((cout << args << "  "), ...);
}
#define debug(x) cout << #x << x << "\n"

typedef pair<int, int> pi;

// compares the second element of the pair (min priority)
struct minComp {
	constexpr bool operator()(pi const& a, pi const& b) {
		return a.second > b.second;
	}
};

typedef priority_queue<pi, vector<pi>, minComp> MinQueue;
#define int_max numeric_limits<int>::max()

void addEdge(unordered_map<int, vector<pi>>& graph, int source, int dest, int weight) {
	if (graph.find(source) ==
			graph.end())  // source does not exist in the graph
		graph.insert({source, vector<pi>{make_pair(dest, weight)}});
	else
		graph[source].push_back(make_pair(dest, weight));

	// adds an edge from dest to the source
	if (graph.find(dest) == graph.end()) addEdge(graph, dest, source, weight);
}

void print(unordered_map<int, vector<pi>>& graph) {
	for (auto adjList = graph.begin(); adjList != graph.end(); ++adjList) {
		cout << adjList->first << " --> ";
		for (pair<int, int> nodes : adjList->second) {
			cout << nodes.first << ": " << nodes.second << " ";
		}
		cout << "\n";
	}
}

// gets the direct edge distance between two nodes
int get_distance(unordered_map<int, vector<pi>> graph, int source, int dest) {
	for (pair<int, int> paths : graph[source])
		if (paths.first == dest) return paths.second;
	return -1;
}

void printQueue(MinQueue q) {
	write("Printing queue \n");
	while (!q.empty()) {
		write(q.top().first);
		q.pop();
	}
}

void show_prevNodes(unordered_map<int, int> prevNodes) {
	write("showing prevNodes [\n");
	for (auto itr = prevNodes.begin(); itr != prevNodes.end(); ++itr) {
		write("(", itr->first, ",", itr->second, ") \n");
	}
	write("] \n");
}

void show_queue(MinQueue q) {
	write("\n showing queue [\n");
	while (!q.empty()) {
		write(q.top().first, ",", q.top().second, "\n");
		q.pop(); } write("]\n"); }

		void empty_queue(MinQueue& q) {
			while (!q.empty()) {
				q.pop();
			}
		}

void copy_queue(MinQueue q1, MinQueue& q2) {
	empty_queue(q2);
	while (!q1.empty()) {
		q2.push(q1.top());
		q1.pop();
	}
}

// updates and element in the queue
void update_queue(MinQueue& q, int index, int updated_weight) {
	MinQueue q2, q1;
	copy_queue(q, q1);
	while(!q1.empty()) {
		pair<int, int> current = q1.top();
		if(current.first != index)
			q2.push(current);
		q1.pop();
	}
	q2.push(make_pair(index,updated_weight));
	copy_queue(q2, q);
}

// *-> main function for dijsktra's shortest path
void shortest_path(unordered_map<int, vector<pi>> graph, int source, int dest, int n) {
	write("Finding the shortest Path ... \n");
	MinQueue q;
	unordered_map<int, int> prevNodes;  // stores the previous visited node
	unordered_map<int, int> assumed_weights;
	vector<bool> visited(n);

	for (int i = 0; i < visited.size(); i++) visited[i] = false;

	// initialize the every vertices' weight as +infinity
	for (auto itr = graph.begin(); itr != graph.end(); ++itr) {
		if (itr->first != source) {
			q.push(make_pair(itr->first, int_max));
			assumed_weights.insert(make_pair(itr->first, int_max));
		}
	}
	q.push(make_pair(source, 0));
	assumed_weights.insert(make_pair(source, 0));

	while (!q.empty()) {
		pi current = q.top();
		if(!visited[current.first]) {
			// relax the adj vertices
			for (pi p : graph[current.first]) {  // looping through the adj elements
				int d = get_distance(graph, current.first, p.first);
				if (current.second + d < assumed_weights[p.first] && !visited[p.first]) {
					int updated_weight = current.second + d;

					update_queue(q, p.first, updated_weight);
					assumed_weights[p.first] = updated_weight;

					if(prevNodes.find(p.first) == prevNodes.end())
						prevNodes.insert(make_pair(p.first, current.first));
					else
						prevNodes[p.first] = current.first;
				}
			}
		}
		q.pop();
	}

	// back tracking from dest vertex
	int i = dest;
	stack<int> s;
	s.push(i);
	while(i != source) {
		s.push(prevNodes[i]);
		i = prevNodes[i];
	}

	write("\n Printing the path : ");
	while(!s.empty()) {
		write(s.top());
		s.pop();
	}
}

int main() {
	unordered_map<int, vector<pi>> graph;
	cout << "Dijstra's shoortest path" << "\n";
	addEdge(graph, 0, 1, 4); 
    addEdge(graph, 0, 7, 8); 
    addEdge(graph, 1, 2, 8); 
    addEdge(graph, 1, 7, 11); 
    addEdge(graph, 2, 3, 7); 
    addEdge(graph, 2, 8, 2); 
    addEdge(graph, 2, 5, 4); 
    addEdge(graph, 3, 4, 9); 
    addEdge(graph, 3, 5, 14); 
    addEdge(graph, 4, 5, 10); 
    addEdge(graph, 5, 6, 2); 
    addEdge(graph, 6, 7, 1); 
    addEdge(graph, 6, 8, 6); 
    addEdge(graph, 7, 8, 7);
	shortest_path(graph, 1, 4, 9);
	return 0;
}
