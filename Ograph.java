import java.util.*;
/**
 * @author Shane Wang
 * This code uses Depth-First Search (dfs) to solve the following problem: 
 * Given a list of connections, return an int[] with the same number of entries 
 * as there are connected components in the graph. 
 * The returned array should be sorted.
 */
public class Ograph {
	Map<String,Set<String>> myGraph;
	Set<String> myVisited;
	public int[] components(String[] data) {
		makeGraph(data);
		myVisited = new TreeSet<>();
		ArrayList<Integer> list = new ArrayList<>();
		for(String v : myGraph.keySet()) {
			if (! myVisited.contains(v)) {
				list.add(compSize(v));
			}
		}
		int[] ret = new int[list.size()];
		for(int k=0; k < list.size(); k++) {
			ret[k] = list.get(k);
		}
		Arrays.sort(ret);
		return ret;
	}
	
	private int compSize(String v) {
		Set<String> visited = new TreeSet<>();
		Stack<String> s = new Stack<>();
		visited.add(v);
		s.add(v);
		while (s.size() > 0) {
			v = s.pop();
			for(String adj : myGraph.get(v)) {
				if (! visited.contains(adj)) {
					s.push(adj);
					visited.add(adj);
				}
			}
		}
		myVisited.addAll(visited);
		return visited.size();
	}

	private void makeGraph(String[] data) {
		myGraph = new TreeMap<>();
		for(int k=0; k < data.length; k++) {
			String s = data[k];
			String v = ""+k;
			String[] adj = s.split(" ");
			for(String a : adj) {
				myGraph.putIfAbsent(v, new TreeSet<>());
				myGraph.putIfAbsent(a, new TreeSet<>());
				myGraph.get(v).add(a);
				myGraph.get(a).add(v);
			}
		}
		//System.out.println(myGraph);
	}
	
}