[BaseContainerProps()]
class AER_UserObject
{
	[Attribute(defvalue: "", uiwidget: UIWidgets.EditBox, desc: "Username - must be unique", params: "", category: "Advanced Equipment")]
	protected string m_sUsername;
	
	[Attribute(defvalue: "", uiwidget: UIWidgets.EditBox, desc: "Password - don't set it to empty string for security reasons", params: "", category: "Advanced Equipment")]
	protected string m_sPassword;
	
	[Attribute(defvalue: "", uiwidget: UIWidgets.CheckBox, desc: "Login allowed - for example the root user is not allowed", params: "", category: "Advanced Equipment")]
	protected bool m_bLoginAllowed;
	
	/*	
	//------------------------------------------------------------------------------------------------
	void AER_UserObject(string username, string password, bool loginAllowed)
	{
		m_sUsername = username;
		m_sPassword = password;
		m_bLoginAllowed = loginAllowed;
	}
	
	// Attributes in conjunction with constructor functions does not seem to work well 
	// So the member variables need to be public and can be set like this: 
	
	AER_UserObject userNew = new AER_UserObject();
	userNew.m_sUsername = "sebastian";
	userNew.m_sPassword = "sebastian123";
	userNew.m_bLoginAllowed = true;
	
	// But we could create an Init() function to do the same:
	
	AER_UserObject userNew = new AER_UserObject();
	userNew.Init("sebastian", "sebastian123", true);

	*/

	//------------------------------------------------------------------------------------------------
	void Init(string username, string password, bool loginAllowed)
	{
		m_sUsername = username;
		m_sPassword = password;
		m_bLoginAllowed = loginAllowed;
	}

	//------------------------------------------------------------------------------------------------
	bool IsLoginAllowed()
	{
		return m_bLoginAllowed;
	}
	
	//------------------------------------------------------------------------------------------------
	string GetUsername()
	{
		return m_sUsername;
	}
	
	//------------------------------------------------------------------------------------------------
	string GetPassword()
	{
		return m_sPassword;
	}
}