package us.quizpl.app.model;

import java.util.ArrayList;
import java.util.List;

import com.google.gson.JsonArray;
import com.google.gson.JsonObject;

public class PrelimsState {
	public static JsonObject getPrelimsStateAsJson(){
		ArrayList<TeamInfo> teams = TeamInfo.getAllTeams();
		
		JsonArray jsonArray = new JsonArray();
		for(TeamInfo team : teams) {
			jsonArray.add(team.toJsonObject());
		}
		
		JsonObject jobjOuter = new JsonObject();
		jobjOuter.add("teams", jsonArray);
		return jobjOuter;
	}
	
	public static void updateStateFromJson(JsonObject jsonObj){
		TeamInfo.getOrCreateFromJson(jsonObj);
	}
}
