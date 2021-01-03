package us.quizpl.puzzle.model;

public enum Company {
	MICROSOFT("Microsoft"), GOOGLE("Google");

	private final String name;

	private Company(String name) {
		this.name = name;
	}

	public String getName() {
		return this.name;
	}
}
