[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class AER_UsersComponentClass : ScriptComponentClass
{
}

class AER_UsersComponent : ScriptComponent
{
	protected ref map<string, ref AER_UserObject> m_mUsers;
	
	protected string m_sUserLoggedIn;
	
	//------------------------------------------------------------------------------------------------
	void AER_UsersComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_mUsers = new map<string, ref AER_UserObject>();
		
		AER_UserObject root = new AER_UserObject("root", "", false);
		
		SetUser("root", root);
		SetUserLoggedIn("");
	}

	//------------------------------------------------------------------------------------------------
	void SetUser(string username, AER_UserObject user)
	{
		m_mUsers.Set(username, user);
		
		PrintFormat("New User Obj Count: %1", m_mUsers.Count());
	}
	
	//------------------------------------------------------------------------------------------------
	AER_UserObject GetUser(string username)
	{
		// returns NULL if not found
		return m_mUsers.Get(username);
	}

	//------------------------------------------------------------------------------------------------
	void SetUserLoggedIn(string username)
	{
		m_sUserLoggedIn = username;
	}
	
	//------------------------------------------------------------------------------------------------
	string GetUserLoggedIn()
	{
		return m_sUserLoggedIn;
	}
}