package us.quizpl.app.model;

import java.util.ArrayList;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

public class PrelimsAccessor implements TeamInfoAccessor {
	@Override
	public JsonObject getTeamsAsJson(){
		ArrayList<TeamInfo> teams = TeamInfo.getAllTeams();
		
		JsonArray jsonArray = new JsonArray();
		for(TeamInfo team : teams) {
			jsonArray.add(team.toJsonObject());
		}
		
		JsonObject jobjOuter = new JsonObject();
		jobjOuter.add("teams", jsonArray);
		return jobjOuter;
	}
	
	@Override
	public void updateStateFromJson(JsonObject jsonObj){
		TeamInfo.getOrCreateFromJson(jsonObj);
	}
}
