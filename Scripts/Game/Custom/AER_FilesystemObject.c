enum EFilesystemObjectType
{
	FILE,
	DIRECTORY
}

enum EFileContentType
{
	TEXT,
	IMAGE,
	EXECUTEABLE
}

class AER_FilesystemObject
{
	protected EFilesystemObjectType m_eType;
	protected EFileContentType m_eContentType;
	protected string m_sContent;
	
	//------------------------------------------------------------------------------------------------
	void AER_FilesystemObject(EFilesystemObjectType type, EFileContentType contentType, string content)
	{
		m_eType = type;
		m_eContentType = contentType;
		m_sContent = content;
	}

	//------------------------------------------------------------------------------------------------
	string GetContent()
	{
		return m_sContent;
	}
}