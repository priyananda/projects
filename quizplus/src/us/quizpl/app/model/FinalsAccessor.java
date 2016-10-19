package us.quizpl.app.model;

import java.util.ArrayList;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

public class FinalsAccessor implements TeamInfoAccessor {
	@Override
	public JsonObject getTeamsAsJson(){
		ArrayList<Finalist> teams = Finalist.getAllTeams();
		
		JsonArray jsonArray = new JsonArray();
		for(Finalist team : teams) {
			jsonArray.add(team.toJsonObject());
		}
		
		JsonObject jobjOuter = new JsonObject();
		jobjOuter.add("teams", jsonArray);
		return jobjOuter;
	}
	
	@Override
	public void updateStateFromJson(JsonObject jsonObj){
		Finalist.getOrCreateFromJson(jsonObj);
	}
}

