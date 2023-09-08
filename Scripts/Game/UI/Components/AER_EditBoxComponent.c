enum EKeyCode
{
	RETURN = 13
}

//------------------------------------------------------------------------------------------------
class AER_EditBoxComponent : SCR_ScriptedWidgetComponent
{
	ref ScriptInvoker m_OnMouseButtonDown = new ScriptInvoker();
	ref ScriptInvoker m_OnKeyDown = new ScriptInvoker();
	ref ScriptInvoker m_OnKeyPress = new ScriptInvoker();
	ref ScriptInvoker m_OnChange = new ScriptInvoker();
	ref ScriptInvoker m_OnUpdate = new ScriptInvoker();
	
	/*
	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		// 0 = Left Mouse button
		// 1 = Right Mouse Button
		// 2 = Middle Mouse Button
		
		PrintFormat("AER OnMouseButtonDown: %1", button);
		
		if (m_OnMouseButtonDown)
			m_OnMouseButtonDown.Invoke(w);
		
		return false;
	}
	*/
	
	/*
	//------------------------------------------------------------------------------------------------
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		PrintFormat("AER OnKeyDown: %1", key);
		
		if (m_OnKeyDown)
			m_OnKeyDown.Invoke(w);
		
		return super.OnKeyDown(w, x, y, key);
	}
	*/

	//------------------------------------------------------------------------------------------------
	override bool OnKeyPress(Widget w, int x, int y, int key)
	{
		// 13			: Return/Enter 
		// 32			: Space 
		// 8 			: Backspace
		// no event 	: Delete
		// 97			: a
		// 65			: A (Shift + a)
		// 47			: /
		// 49			: 1
		// 9			: Tabulator
		// no event		: Shift
		// no event		: Control
		// no event		: Alt
		// 10			: Control + Return
		// no event		: Caps Lock
		
		// KeyCode.KC_SPACE
		// this enum uses other codes, for example 'Return' is 28 instead of 13
		// I can't use this enum for this case, but I could build my own
		
		
		PrintFormat("AER OnKeyPress: %1", key);
		
		if (m_OnKeyPress)
			m_OnKeyPress.Invoke(w, x, y, key);
		
		return super.OnKeyPress(w, x, y, key);
	}
	
	/*
	//------------------------------------------------------------------------------------------------
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		// triggers if content changes or on some special keys, like 'Del' which does not
		// fire the 'OnKeyPress' event
		
		PrintFormat("AER OnChange: %1", finished);
		
		if (m_OnChange)
			m_OnChange.Invoke(w);
		
		return super.OnChange(w, x, y, key);
	}
	*/
	
	/*
	//------------------------------------------------------------------------------------------------
	override bool OnUpdate(Widget w)
	{
		PrintFormat("AER OnUpdate");
		
		if (m_OnUpdate)
			m_OnUpdate.Invoke(w);
		
		return super.OnUpdate(w, x, y, key);
	}
	*/

	//------------------------------------------------------------------------------------------------
	static AER_EditBoxComponent GetEditBoxComponent(string name, Widget parent, bool searchAllChildren = true)
	{
		auto component = AER_EditBoxComponent.Cast(GetComponent(AER_EditBoxComponent, name, parent, searchAllChildren));
		
		return component;
	}
}