[BaseContainerProps(), SCR_BaseContainerCustomTitleField("m_sName")]
class AER_FileObject : AER_FilesystemObject
{
	[Attribute(defvalue: "0", uiwidget: UIWidgets.ComboBox, desc: "Content Type (Text, Image, Executable)", params: "", enums: ParamEnumArray.FromEnum(EFileContentType), category: "Advanced Equipment")]
	protected EFileContentType m_eContentType;

	[Attribute(defvalue: "", uiwidget: UIWidgets.EditBoxMultiline, desc: "Name - must be unique in it's parent folder", params: "", category: "Advanced Equipment")]
	protected string m_sContent;
	
	//------------------------------------------------------------------------------------------------
	EFileContentType GetContentType()
	{
		return m_eContentType;
	}
	
	//------------------------------------------------------------------------------------------------
	string GetContent()
	{
		return m_sContent;
	}
}