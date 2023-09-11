/*

This is a universal component for UI widgets to allow invoking code 
for various UI events.

UI Widget: Text

Supported UI Events:
  - OnUpdate

*/

//------------------------------------------------------------------------------------------------
class AER_TextComponent : AER_ScriptedWidgetComponent
{
	ref ScriptInvoker m_OnUpdate = new ScriptInvoker();
	
	//------------------------------------------------------------------------------------------------
	override bool OnUpdate(Widget w)
	{
		// is fired every time the content is changed for example with 'SetText'
		
		PrintFormat("AER Text Component OnUpdate: %1", w);
		
		if (m_OnUpdate)
			m_OnUpdate.Invoke(w);
		
		return super.OnUpdate(w);
	}

	//------------------------------------------------------------------------------------------------
	static AER_TextComponent GetTextComponent(string name, Widget parent, bool searchAllChildren = true)
	{
		auto component = AER_TextComponent.Cast(GetComponent(AER_TextComponent, name, parent, searchAllChildren));
		
		return component;
	}
}