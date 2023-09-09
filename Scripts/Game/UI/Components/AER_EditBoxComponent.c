enum EKeyCode
{
	RETURN 		= 13,
	A 			= 97,
	B 			= 98,
	C 			= 99
}

//------------------------------------------------------------------------------------------------
class AER_EditBoxComponent : SCR_ScriptedWidgetComponent
{
	ref ScriptInvoker m_OnMouseButtonDown = new ScriptInvoker();
	ref ScriptInvoker m_OnKeyDown = new ScriptInvoker();
	ref ScriptInvoker m_OnKeyPress = new ScriptInvoker();
	ref ScriptInvoker m_OnChange = new ScriptInvoker();
	ref ScriptInvoker m_OnUpdate = new ScriptInvoker();
	ref ScriptInvoker m_OnFocus = new ScriptInvoker();
	ref ScriptInvoker m_OnFocusLost = new ScriptInvoker();
	
	ref ScriptInvoker m_HandlerAttached = new ScriptInvoker();
	ref ScriptInvoker m_HandlerDeattached = new ScriptInvoker();
	
	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		// works for EditBox
		
		// 0 = Left Mouse button
		// 1 = Right Mouse Button
		// 2 = Middle Mouse Button
		
		PrintFormat("AER EditBox Component OnMouseButtonDown: %1", button);
		
		if (m_OnMouseButtonDown)
			m_OnMouseButtonDown.Invoke(w);
		
		return false;	
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		PrintFormat("AER EditBox Component OnKeyDown: %1", key);
		
		if (m_OnKeyDown)
			m_OnKeyDown.Invoke(w);
		
		return super.OnKeyDown(w, x, y, key);
	}

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
		
		//PrintFormat("AER EditBox Component OnKeyPress: %1", key);
		
		if (m_OnKeyPress)
			m_OnKeyPress.Invoke(w, x, y, key);
		
		return super.OnKeyPress(w, x, y, key);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		// works for EditBox; 'finished' is 0 until pressing 'Return' or 'Enter'; then it becomes 1
		
		PrintFormat("AER EditBox Component OnChange: %1", finished);
		
		if (m_OnChange)
			m_OnChange.Invoke(w);
		
		return super.OnChange(w, x, y, finished);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnUpdate(Widget w)
	{
		// works for EditBox; Fires wenn pressing 'Return' or 'Enter'
		
		PrintFormat("AER EditBox Component OnUpdate");
		
		if (m_OnUpdate)
			m_OnUpdate.Invoke(w);
		
		return super.OnUpdate(w);
	}

	//------------------------------------------------------------------------------------------------
	override bool OnFocus(Widget w, int x, int y)
	{
		// works for EditBox; Fires when getting the focus
		
		PrintFormat("AER EditBox Component OnFocus");
		
		if (m_OnUpdate)
			m_OnUpdate.Invoke(w);
		
		return super.OnFocus(w, x, y);
	}
	
	//------------------------------------------------------------------------------------------------	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		// works for EditBox; Fires when losing the focus
		
		PrintFormat("AER EditBox Component OnFocusLost");
		
		if (m_OnUpdate)
			m_OnUpdate.Invoke(w);
		
		return super.OnFocusLost(w, x, y);
	}

	//------------------------------------------------------------------------------------------------
	override void HandlerAttached(Widget w)
	{
		// works for EditBox; Fires when the component is attached to the editbox (on menu/dialog start)
		
		super.HandlerAttached(w);
		
		PrintFormat("AER EditBox Component HandlerAttached");
		
		if (m_HandlerAttached)
			m_HandlerAttached.Invoke(w);
	}
	
	//------------------------------------------------------------------------------------------------
	override void HandlerDeattached(Widget w)
	{
		// works for EditBox; Fires when the component is deattached to the editbox (on menu/dialog end)
		
		super.HandlerDeattached(w);
		
		PrintFormat("AER EditBox Component HandlerDeattached");
		
		if (m_HandlerDeattached)
			m_HandlerDeattached.Invoke(w);
	}
	
	//------------------------------------------------------------------------------------------------
	static AER_EditBoxComponent GetEditBoxComponent(string name, Widget parent, bool searchAllChildren = true)
	{
		auto component = AER_EditBoxComponent.Cast(GetComponent(AER_EditBoxComponent, name, parent, searchAllChildren));
		
		return component;
	}
}