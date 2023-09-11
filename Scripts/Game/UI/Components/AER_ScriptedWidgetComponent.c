//! parent of all Scripted Widgets, even non-interactive ones
class AER_ScriptedWidgetComponent : ScriptedWidgetComponent
{
	protected Widget m_wRoot;

	//------------------------------------------------------------------------------------------------
	override void HandlerAttached(Widget w)
	{
		m_wRoot = w;
	}

	//------------------------------------------------------------------------------------------------
	//! Base method for component lookup through the widget library
	static AER_ScriptedWidgetComponent GetComponent(typename componentType, string name, Widget parent, bool searchAllChildren = true)
	{
		if (!parent || name == string.Empty)
			return null;

		Widget w;
		if (searchAllChildren)
			w = parent.FindAnyWidget(name);
		else
			w = parent.FindWidget(name);

		if (!w)
		{
			Print(string.Format("AER_ScriptedWidgetComponent.GetComponent: widget not found: %1 %2", componentType, name), LogLevel.WARNING);
			Debug.DumpStack();
			return null;
		}

		return AER_ScriptedWidgetComponent.Cast(w.FindHandler(componentType));
	}

	//------------------------------------------------------------------------------------------------
	Widget GetRootWidget()
	{
		return m_wRoot;
	}
};
