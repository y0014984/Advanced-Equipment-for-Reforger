[ComponentEditorProps(category: "GameScripted/Misc", description: "")]
class AER_UsersComponentClass : ScriptComponentClass
{
}

class AER_UsersComponent : ScriptComponent
{
	[Attribute(defvalue: "", uiwidget: UIWidgets.Object, desc: "Users - Class AER_UserObject", params: "", category: "Advanced Equipment")];
	protected ref array<ref AER_UserObject> m_aUsers;
	
	[Attribute(defvalue: "", uiwidget: UIWidgets.EditBox, desc: "User Logged In - Name of the user", params: "", category: "Advanced Equipment")];
	protected string m_sUserLoggedIn;

	//------------------------------------------------------------------------------------------------
	void AddUser(AER_UserObject user)
	{
		m_aUsers.Insert(user);
	}
	
	//------------------------------------------------------------------------------------------------
	AER_UserObject GetUserByUsername(string username)
	{
		foreach (ref AER_UserObject user : m_aUsers)
		{
			if (user.GetUsername() == username)
				return user;
		}
		
		// returns NULL if not found
		return null;
	}

	//------------------------------------------------------------------------------------------------
	ref array<ref AER_UserObject> GetUsers()
	{
		return m_aUsers;
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