/*

This is a universal component for UI widgets to allow invoking code 
for various UI events.

UI Widget: Text

Supported UI Events:
  - OnClick
  - OnDoubleClick

*/

//------------------------------------------------------------------------------------------------
class AER_ButtonComponent : AER_ScriptedWidgetComponent
{
	ref ScriptInvoker m_OnClick = new ScriptInvoker();
	ref ScriptInvoker m_OnDoubleClick = new ScriptInvoker();
	
	//------------------------------------------------------------------------------------------------
	override bool OnClick(Widget w, int x, int y, int button)
	{
		// works for Button; Probably fires; not sure
		
		// 0 = Left Mouse Button
		// 1 = Right Mouse Button
		// 2 = Middle Mouse Button
		
		PrintFormat("AER Button Component OnClick: %1 %2 %3 %4", w, x, y, button);
		
		if (m_OnClick)
			m_OnClick.Invoke(w, x, y, button);
		
		return super.OnClick(w, x, y, button);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		// works for Button; Fires on Double Click, even if the widget is already in focus
		
		// 0 = Left Mouse Button
		// 1 = Right Mouse Button
		// 2 = Middle Mouse Button
		
		PrintFormat("AER Button Component OnDoubleClick: %1 %2 %3 %4", w, x, y, button);
		
		if (m_OnDoubleClick)
			m_OnDoubleClick.Invoke(w, x, y, button);
		
		return super.OnDoubleClick(w, x, y, button);	
	}

	//------------------------------------------------------------------------------------------------
	static AER_ButtonComponent GetButtonComponent(string name, Widget parent, bool searchAllChildren = true)
	{
		auto component = AER_ButtonComponent.Cast(GetComponent(AER_ButtonComponent, name, parent, searchAllChildren));
		
		return component;
	}
}