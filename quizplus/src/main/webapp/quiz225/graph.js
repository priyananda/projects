class Node {
	constructor(label, stateSet){
		this.label = label;
		this.stateSet = stateSet;
		this.links = new Map();
	}
	get getNextLinks() {
		return this.links.keys();
	}
	getNode(nextTeamId) {
		return this.links.get(nextTeamId);
	}
	addLink(nextTeamId, nextNode) {
		console.log([...this.stateSet] + " + " + nextTeamId + " = " + [...nextNode.stateSet]);
		this.links.set(nextTeamId, nextNode);
	}
}

class Graph {
	constructor() {
		this.buildGraph();
		this.currentTeam = 1;
		this.lastQuestion = 12;
		this.currentQuestion = 1;
		this.currentNode = this.A;
	}
	shouldShowLinks(questionId) {
		return this.currentQuestion.toString() === questionId &&
			this.currentQuestion !== this.lastQuestion;
	}
	get getLinks() {
		var links = this.currentNode.getNextLinks;
		return [...links];
	}
	get getCurrentQuestion() {
		return this.currentQuestion;
	}
	advance(nextTeamId) {
		this.currentTeam = nextTeamId;
		this.currentQuestion++;
		this.currentNode = this.currentNode.getNode(nextTeamId);
	}
	buildGraph() {
		this.A = new Node("A", new Set([1]));
		this.B = new Node("B", new Set([1, 2]));
		this.C = new Node("C", new Set([1, 4]));
		this.D = new Node("D", new Set([1, 3]));
		this.E = new Node("E", new Set([1, 2, 3]));
		this.F = new Node("F", new Set([1, 2, 4]));
		this.G = new Node("G", new Set([1, 3, 4]));
		this.H = new Node("H", new Set([1, 2, 3, 5]));
		this.I = new Node("I", new Set([1, 2, 3, 4]));
		this.J = new Node("J", new Set([1, 3, 4, 5]));
		this.K = new Node("K", new Set([1, 2, 3, 5, 6]));
		this.L = new Node("L", new Set([1, 2, 3, 4, 6]));
		this.M = new Node("M", new Set([1, 2, 3, 4, 5]));
		this.N = new Node("N", new Set([1, 3, 4, 5, 6]));
		this.O = new Node("O", new Set([1, 2, 3, 4, 5, 6]));
		this.P1 = new Node("P1", new Set([1]));
		this.P2 = new Node("P2", new Set([3]));
		this.P3 = new Node("P3", new Set([1, 5]));
		this.P4 = new Node("P4", new Set([1, 3]));
		this.P5 = new Node("P5", new Set([3, 4]));
		this.P6 = new Node("P6", new Set([1, 5, 6]));
		this.P7 = new Node("P7", new Set([1, 3, 5]));
		this.P8 = new Node("P8", new Set([1, 3, 4]));
		this.P9 = new Node("P9", new Set([2, 3, 4]));
		this.Q1 = new Node("Q1", new Set([1, 4, 5, 6]));
		this.Q2 = new Node("Q2", new Set([1, 3, 5, 6]));
		this.Q3 = new Node("Q3", new Set([1, 3, 4, 5]));
		this.Q4 = new Node("Q4", new Set([1, 2, 3, 4]));
		this.Q5 = new Node("Q5", new Set([1, 3, 4, 5, 6]));
		this.Q6 = new Node("Q6", new Set([1, 2, 3, 4, 5]));
		this.Q7 = new Node("Q7", new Set([1, 2, 3, 4, 6]));
		this.Q8 = new Node("Q8", new Set([1, 2, 3, 4, 5, 6]));
		
		this.A.addLink(2, this.B); this.A.addLink(4, this.C); this.A.addLink(3, this.D);
		this.B.addLink(3, this.E); this.B.addLink(4, this.F);
		this.C.addLink(2, this.F); this.C.addLink(3, this.G);
		this.D.addLink(2, this.E); this.D.addLink(4, this.G);
		this.E.addLink(5, this.H); this.E.addLink(4, this.I);
		this.F.addLink(3, this.I);
		this.G.addLink(2, this.I); this.G.addLink(5, this.J);
		this.H.addLink(6, this.K); this.H.addLink(4, this.M);
		this.I.addLink(6, this.L); this.I.addLink(5, this.M);
		this.J.addLink(2, this.M); this.J.addLink(6, this.N);
		this.K.addLink(4, this.O);
		this.L.addLink(5, this.O);
		this.M.addLink(6, this.O);
		this.N.addLink(2, this.O);
		
		this.O.addLink(1, this.P1);  this.O.addLink(3, this.P2);
		this.P1.addLink(5, this.P3); this.P1.addLink(3, this.P4);
		this.P2.addLink(1, this.P4); this.P2.addLink(4, this.P5);
		this.P3.addLink(6, this.P6); this.P3.addLink(3, this.P7);
		this.P4.addLink(5, this.P7); this.P4.addLink(4, this.P8);
		this.P5.addLink(1, this.P8); this.P5.addLink(2, this.P9);
		this.P6.addLink(4, this.Q1); this.P6.addLink(3, this.Q2);
		this.P7.addLink(6, this.Q2); this.P7.addLink(4, this.Q3);
		this.P8.addLink(5, this.Q3); this.P8.addLink(2, this.Q4);
		this.P9.addLink(1, this.Q4);
		this.Q1.addLink(3, this.Q5);
		this.Q2.addLink(4, this.Q5);
		this.Q3.addLink(6, this.Q5); this.Q3.addLink(2, this.Q6);
		this.Q4.addLink(5, this.Q6); this.Q4.addLink(6, this.Q7);
		this.Q5.addLink(2, this.Q8);
		this.Q6.addLink(6, this.Q8);
		this.Q7.addLink(5, this.Q8);
	}
}