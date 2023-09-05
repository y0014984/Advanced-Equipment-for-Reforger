[BaseContainerProps()]
class AER_Permissions
{
	[Attribute(defvalue: "root", uiwidget: UIWidgets.EditBox, desc: "Owner of the filesystem object", params: "", category: "Advanced Equipment")];
	protected string m_sOwner;
	
	[Attribute(defvalue: "1", uiwidget: UIWidgets.CheckBox, desc: "Owner Read", params: "", category: "Advanced Equipment")];
	protected bool m_bOwnerRead;
	
	[Attribute(defvalue: "1", uiwidget: UIWidgets.CheckBox, desc: "Owner Write", params: "", category: "Advanced Equipment")];
	protected bool m_bOwnerWrite;
	
	[Attribute(defvalue: "0", uiwidget: UIWidgets.CheckBox, desc: "Owner Execute", params: "", category: "Advanced Equipment")];
	protected bool m_bOwnerExecute;
	
	[Attribute(defvalue: "1", uiwidget: UIWidgets.CheckBox, desc: "Everyone Read", params: "", category: "Advanced Equipment")];
	protected bool m_bEveryoneRead;
	
	[Attribute(defvalue: "1", uiwidget: UIWidgets.CheckBox, desc: "Everyone Write", params: "", category: "Advanced Equipment")];
	protected bool m_bEveryoneWrite;
	
	[Attribute(defvalue: "0", uiwidget: UIWidgets.CheckBox, desc: "Everyone Execute", params: "", category: "Advanced Equipment")];
	protected bool m_bEveryoneExecute;
}