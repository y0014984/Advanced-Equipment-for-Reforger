//------------------------------------------------------------------------------------------------
class AER_TextComponent : SCR_ScriptedWidgetComponent
{
	ref ScriptInvoker m_OnMouseButtonDown = new ScriptInvoker();
	ref ScriptInvoker m_OnKeyDown = new ScriptInvoker();
	ref ScriptInvoker m_OnKeyUp = new ScriptInvoker();
	ref ScriptInvoker m_OnKeyPress = new ScriptInvoker();
	ref ScriptInvoker m_OnChange = new ScriptInvoker();
	ref ScriptInvoker m_OnUpdate = new ScriptInvoker();
	
	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		// does not work on TextWidget
		
		// 0 = Left Mouse button
		// 1 = Right Mouse Button
		// 2 = Middle Mouse Button
		
		PrintFormat("AER Text Component OnMouseButtonDown: %1", button);
		
		if (m_OnMouseButtonDown)
			m_OnMouseButtonDown.Invoke(w);
		
		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnKeyPress(Widget w, int x, int y, int key)
	{
		// does not work on TextWidget
		
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
		
		PrintFormat("AER Text Component OnKeyPress: %1", key);
		
		if (m_OnKeyPress)
			m_OnKeyPress.Invoke(w, x, y, key);
		
		return super.OnKeyPress(w, x, y, key);
	}

	//------------------------------------------------------------------------------------------------
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		// does not work on TextWidget
		
		PrintFormat("AER Text Component OnKeyDown: %1", key);
		
		if (m_OnKeyDown)
			m_OnKeyDown.Invoke(w, x, y, key);
		
		return super.OnKeyDown(w, x, y, key);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnKeyUp(Widget w, int x, int y, int key)
	{
		// does not work on TextWidget
		
		PrintFormat("AER Text Component OnKeyUp: %1", key);
		
		if (m_OnKeyUp)
			m_OnKeyUp.Invoke(w, x, y, key);
		
		return super.OnKeyUp(w, x, y, key);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		// does not work on TextWidget
		
		PrintFormat("AER Text Component OnChange: %1", finished);
		
		if (m_OnChange)
			m_OnChange.Invoke(w);
		
		return super.OnChange(w, x, y, key);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnUpdate(Widget w)
	{
		// is fired every time the content is changed for example with 'SetText'
		
		PrintFormat("AER Text Component OnUpdate");
		
		if (m_OnUpdate)
			m_OnUpdate.Invoke(w);
		
		return super.OnUpdate(w, x, y, key);
	}

	//------------------------------------------------------------------------------------------------
	override bool OnEvent(EventType eventType, Widget target, int parameter0, int parameter1)
	{
		// fires but the purpose is unclear
		
		PrintFormat("AER Text Component OnEvent eventType: %1", eventType);
		
		if (m_OnUpdate)
			m_OnUpdate.Invoke(target);
		
		return super.OnUpdate(w, x, y, key);
	}

	//------------------------------------------------------------------------------------------------
	static AER_TextComponent GetTextComponent(string name, Widget parent, bool searchAllChildren = true)
	{
		auto component = AER_TextComponent.Cast(GetComponent(AER_TextComponent, name, parent, searchAllChildren));
		
		return component;
	}
}