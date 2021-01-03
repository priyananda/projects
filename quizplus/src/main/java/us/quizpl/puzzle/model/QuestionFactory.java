package us.quizpl.puzzle.model;

import com.google.gson.JsonObject;

public class QuestionFactory {
	public static abstract class Question {
		public void emitContent(JsonObject object) {}
		public String getHint() {return "";}
		public abstract String getAnswerPattern();
	}
	
	public static Question get(CompanyLevel clevel) {
		return QUESTIONS[clevel.getLevel()];
	}
	
	private static Question SOLAR_SORT = new Question() {
		@Override
		public String getAnswerPattern() {
			return "byepluto";
		}
	};
	
	private static Question CALL_ME_MAYBE = new Question() {
		@Override
		public String getAnswerPattern() {
			return "spaceforce";
		}
	};
	
	private static Question ISBN = new Question() {
		@Override
		public String getAnswerPattern() {
			return "victorian";
		}
	};
	
	private static Question C_CODE_DECODE = new Question() {
		@Override
		public String getAnswerPattern() {
			return "marvin";
		}
	};
	
	private static Question APP_KA_SUROOR = new Question() {
		@Override
		public String getAnswerPattern() {
			return "abc";
		}
	};
	
	private static Question CLOSE_UP_ANTAKSHARI = new Question() {
		@Override
		public String getAnswerPattern() {
			return "annukapoor";
		}
	};
	
	private static Question FACE_OFF = new Question() {
		@Override
		public String getAnswerPattern() {
			return "johnwoo";
		}
	};
	
	private static Question CRASS_WORDS = new Question() {
		@Override
		public String getAnswerPattern() {
			return "motherboard";
		}
	};
	
	private static Question QED = new Question() {
		@Override
		public String getAnswerPattern() {
			return "euler";
		}
	};
	
	private static Question SOLO = new Question() {
		@Override
		public String getAnswerPattern() {
			return "aaaaa";
		}
	};
	
	private static Question MISSING = new Question() {
		@Override
		public String getAnswerPattern() {
			return "paris";
		}
	};
	
	private static Question BOOK_CRICKET = new Question() {
		@Override
		public String getAnswerPattern() {
			return "india";
		}
	};
	
	private static Question[] QUESTIONS = new Question[] {
		SOLAR_SORT, // 0
		CALL_ME_MAYBE, // 1
		ISBN, // 2
		C_CODE_DECODE, // 3
		APP_KA_SUROOR, // 4 ejsh
		CLOSE_UP_ANTAKSHARI, // 5
		FACE_OFF, // 6 mabc
		CRASS_WORDS, // 7 dgez
		QED, // 8 lurh
		SOLO, // 9 gcfg
		MISSING, // 10 bwgs
		BOOK_CRICKET, //11 pahf
	};
}
