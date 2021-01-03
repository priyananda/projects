package us.quizpl.puzzle.model;

import java.util.HashMap;
import java.util.Map;

public class CompanyLevel {
	private final Company company;
	private final int level;
	private final String key;

	private static final int MAX_LEVEL = 11;
	private static Map<String, CompanyLevel> LEVEL_BY_KEY = new HashMap<String, CompanyLevel>();
	private static CompanyLevel[][] ORDERED_LEVEL = new CompanyLevel[2][MAX_LEVEL + 1];
	
	private CompanyLevel(Company company, int level, String key) {
		this.company = company;
		this.level = level;
		this.key = key;
	}
	
	public Company getCompany() {
		return this.company;
	}
	
	public int getLevel() {
		return this.level;
	}
	
	public CompanyLevel getNextLevel() {
		if (this.level == MAX_LEVEL)
			return null;
		return of(this.company, this.level + 1);
	}
	
	public CompanyLevel getPeerLevel() {
		if (this.company.equals(Company.MICROSOFT)) {
			int downLevel = 0; 
			// SE2/Senior/Principal become L3/L4/L5
			if (this.level == 1 || this.level == 2 || this.level == 3) {
				downLevel = -1;
			}
			return of(Company.GOOGLE, this.level + downLevel);
		}
		return of(Company.MICROSOFT, this.level);
	}
	
	public String getKey() {
		return this.key;
	}
	
	public static CompanyLevel ofKey(String key) {
		return LEVEL_BY_KEY.get(key);
	}
	
	public static CompanyLevel of(Company company, int level) {
		return ORDERED_LEVEL[company.ordinal()][level];
	}
	
	static {
		ORDERED_LEVEL[0][0] = new CompanyLevel(Company.MICROSOFT, 0, "mxpe");
		ORDERED_LEVEL[0][1] = new CompanyLevel(Company.MICROSOFT, 1, "this");
		ORDERED_LEVEL[0][2] = new CompanyLevel(Company.MICROSOFT, 2, "rnfa");
		ORDERED_LEVEL[0][3] = new CompanyLevel(Company.MICROSOFT, 3, "vghd");
		ORDERED_LEVEL[0][4] = new CompanyLevel(Company.MICROSOFT, 4, "ejsh");
		ORDERED_LEVEL[0][5] = new CompanyLevel(Company.MICROSOFT, 5, "nvqw");
		ORDERED_LEVEL[0][6] = new CompanyLevel(Company.MICROSOFT, 6, "mabc");
		ORDERED_LEVEL[0][7] = new CompanyLevel(Company.MICROSOFT, 7, "dgez");
		ORDERED_LEVEL[0][8] = new CompanyLevel(Company.MICROSOFT, 8, "lurh");
		ORDERED_LEVEL[0][9] = new CompanyLevel(Company.MICROSOFT, 9, "gcfg");
		ORDERED_LEVEL[0][10] = new CompanyLevel(Company.MICROSOFT, 10, "bwgs");
		ORDERED_LEVEL[0][11] = new CompanyLevel(Company.MICROSOFT, 11, "pahf");
		
		for (int j = 0; j <= MAX_LEVEL; ++j)
			LEVEL_BY_KEY.put(ORDERED_LEVEL[0][j].getKey(), ORDERED_LEVEL[0][j]);
	}
}
