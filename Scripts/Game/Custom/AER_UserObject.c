class AER_UserObject
{
	protected string m_sUsername;
	protected string m_sPassword;
	protected bool m_bLoginAllowed;
	
	//------------------------------------------------------------------------------------------------
	void AER_UserObject(string username, string password, bool loginAllowed)
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