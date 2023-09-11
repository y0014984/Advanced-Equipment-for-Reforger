/*

This is a universal component for UI widgets to allow invoking code 
for various UI events.

UI Widget: EditBox

Supported UI Events:
  - OnClick*
  - OnDoubleClick
  - OnFocus
  - OnFocusLost
  - OnMouseEnter
  - OnMouseLeave
  - OnMouseWheel
  - OnMouseButtonDown
  - OnMouseButtonUp
  - OnKeyDown*
  - OnKeyUp*
  - OnKeyPress
  - OnChange
  - OnUpdate
  - HandlerAttached
  - HandlerDeattached

  * seem to be broken but should work from my point of view

*/

// Example enum for key presses. Needs to be completed if used

enum EKeyCode
{
	RETURN 		= 13,
	A 			= 97,
	B 			= 98,
	C 			= 99
}

//------------------------------------------------------------------------------------------------
class AER_EditBoxComponent : AER_ScriptedWidgetComponent
{
	ref ScriptInvoker m_OnClick = new ScriptInvoker();
	ref ScriptInvoker m_OnDoubleClick = new ScriptInvoker();
	
	ref ScriptInvoker m_OnFocus = new ScriptInvoker();
	ref ScriptInvoker m_OnFocusLost = new ScriptInvoker();

	ref ScriptInvoker m_OnMouseWheel = new ScriptInvoker();
		
	ref ScriptInvoker m_OnMouseButtonDown = new ScriptInvoker();
	ref ScriptInvoker m_OnMouseButtonUp = new ScriptInvoker();
	
	ref ScriptInvoker m_OnMouseEnter = new ScriptInvoker();
	ref ScriptInvoker m_OnMouseLeave = new ScriptInvoker();
	
	ref ScriptInvoker m_OnKeyDown = new ScriptInvoker();
	ref ScriptInvoker m_OnKeyUp = new ScriptInvoker();
	ref ScriptInvoker m_OnKeyPress = new ScriptInvoker();
	
	ref ScriptInvoker m_OnChange = new ScriptInvoker();
	ref ScriptInvoker m_OnUpdate = new ScriptInvoker();
	
	ref ScriptInvoker m_HandlerAttached = new ScriptInvoker();
	ref ScriptInvoker m_HandlerDeattached = new ScriptInvoker();

	//------------------------------------------------------------------------------------------------
	override bool OnClick(Widget w, int x, int y, int button)
	{
		// works for EditBox; Probably fires; not sure
		
		// 0 = Left Mouse Button
		// 1 = Right Mouse Button
		// 2 = Middle Mouse Button
		
		PrintFormat("AER EditBox Component OnClick: %1 %2 %3 %4", w, x, y, button);
		
		if (m_OnClick)
			m_OnClick.Invoke(w, x, y, button);
		
		return super.OnClick(w, x, y, button);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnDoubleClick(Widget w, int x, int y, int button)
	{
		// works for EditBox; Fires on Double Click, even if the widget is already in focus
		
		// 0 = Left Mouse Button
		// 1 = Right Mouse Button
		// 2 = Middle Mouse Button
		
		PrintFormat("AER EditBox Component OnDoubleClick: %1 %2 %3 %4", w, x, y, button);
		
		if (m_OnDoubleClick)
			m_OnDoubleClick.Invoke(w, x, y, button);
		
		return super.OnDoubleClick(w, x, y, button);	
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnFocus(Widget w, int x, int y)
	{
		// works for EditBox; Fires when getting the focus
		
		PrintFormat("AER EditBox Component OnFocus: %1 %2 %3", w, x, y);
		
		if (m_OnFocus)
			m_OnFocus.Invoke(w, x, y);
		
		return super.OnFocus(w, x, y);
	}
	
	//------------------------------------------------------------------------------------------------	
	override bool OnFocusLost(Widget w, int x, int y)
	{
		// works for EditBox; Fires when losing the focus
		
		PrintFormat("AER EditBox Component OnFocusLost: %1 %2 %3", w, x, y);
		
		if (m_OnFocusLost)
			m_OnFocusLost.Invoke(w, x, y);
		
		return super.OnFocusLost(w, x, y);
	}

	//------------------------------------------------------------------------------------------------	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		// works for EditBox; Fires when mouse enters area of editbox
		
		PrintFormat("AER EditBox Component OnMouseEnter: %1 %2 %3", w, x, y);
		
		if (m_OnMouseEnter)
			m_OnMouseEnter.Invoke(w, x ,y);
		
		return super.OnMouseEnter(w, x, y);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		// works for EditBox; Fires when mouse leaves area of editbox
		
		PrintFormat("AER EditBox Component OnMouseLeave: %1 %2 %3 %4", w, enterW, x, y);
		
		if (m_OnMouseLeave)
			m_OnMouseLeave.Invoke(w, enterW, x, y);
		
		return super.OnMouseLeave(w, x, y);
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseWheel(Widget w, int x, int y, int wheel)
	{
		// works for EditBox; Fires when scrolling Mouse Wheel up or down
		
		PrintFormat("AER EditBox Component OnMouseWheel: %1 %2 %3 %4", w, x, y, wheel);
		
		if (m_OnMouseWheel)
			m_OnMouseWheel.Invoke(w, x, y, wheel);
		
		return super.OnMouseWheel(w, x, y, wheel);	
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		// works for EditBox; Fires on Mouse Button press
		
		// 0 = Left Mouse Button
		// 1 = Right Mouse Button
		// 2 = Middle Mouse Button
		
		PrintFormat("AER EditBox Component OnMouseButtonDown: %1 %2 %3 %4", w, x, y, button);
		
		if (m_OnMouseButtonDown)
			m_OnMouseButtonDown.Invoke(w, x, y, button);
		
		return super.OnMouseButtonDown(w, x, y, button);	
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		// works for EditBox; Fires on Mouse Button release
		
		// 0 = Left Mouse Button
		// 1 = Right Mouse Button
		// 2 = Middle Mouse Button
		
		PrintFormat("AER EditBox Component OnMouseButtonUp: %1 %2 %3 $4", w, x, y, button);
		
		if (m_OnMouseButtonUp)
			m_OnMouseButtonUp.Invoke(w, x, y, button);
		
		return super.OnMouseButtonUp(w, x, y, button);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnKeyDown(Widget w, int x, int y, int key)
	{
		PrintFormat("AER EditBox Component OnKeyDown: %1 %2 %3 %4", w, x, y, key);
		
		if (m_OnKeyDown)
			m_OnKeyDown.Invoke(w, x, y, key);
		
		return super.OnKeyDown(w, x, y, key);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnKeyUp(Widget w, int x, int y, int key)
	{
		PrintFormat("AER EditBox Component OnKeyUp: %1 %2 %3 %4", w, x, y, key);
		
		if (m_OnKeyUp)
			m_OnKeyUp.Invoke(w, x, y, key);
		
		return super.OnKeyUp(w, x, y, key);
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
		
		PrintFormat("AER EditBox Component OnKeyPress: %1 %2 %3 %4", w, x, y, key);
		
		if (m_OnKeyPress)
			m_OnKeyPress.Invoke(w, x, y, key);
		
		return super.OnKeyPress(w, x, y, key);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		// works for EditBox; 'finished' is 0 until pressing 'Return' or 'Enter'; then it becomes 1
		
		PrintFormat("AER EditBox Component OnChange: %1 %2 %3 %4", w, x, y, finished);
		
		if (m_OnChange)
			m_OnChange.Invoke(w, x, y, finished);
		
		return super.OnChange(w, x, y, finished);
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnUpdate(Widget w)
	{
		// works for EditBox; Fires when using for example SetText()
		
		PrintFormat("AER EditBox Component OnUpdate: %1", w);
		
		if (m_OnUpdate)
			m_OnUpdate.Invoke(w);
		
		return super.OnUpdate(w);
	}

	//------------------------------------------------------------------------------------------------
	override void HandlerAttached(Widget w)
	{
		// works for EditBox; Fires when the component is attached to the editbox (on menu/dialog start)
		
		super.HandlerAttached(w);
		
		PrintFormat("AER EditBox Component HandlerAttached: %1", w);
		
		if (m_HandlerAttached)
			m_HandlerAttached.Invoke(w);
	}
	
	//------------------------------------------------------------------------------------------------
	override void HandlerDeattached(Widget w)
	{
		// works for EditBox; Fires when the component is deattached to the editbox (on menu/dialog end)
		
		super.HandlerDeattached(w);
		
		PrintFormat("AER EditBox Component HandlerDeattached: %1", w);
		
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