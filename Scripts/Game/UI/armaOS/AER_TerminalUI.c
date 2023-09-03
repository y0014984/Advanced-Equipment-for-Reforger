class AER_TerminalUI : MenuBase
{
	protected static const string TERMINAL = "Terminal";
	protected static const string BUTTON_CLOSE = "ButtonClose";
	protected static const string BUTTON_ACTION = "ButtonAction";
	
	protected AER_OpenCloseStateComponent m_OpenCloseStateComponent;

	//------------------------------------------------------------------------------------------------
	protected override void OnMenuOpen()
	{
		Print("OnMenuOpen: Terminal opened!", LogLevel.NORMAL);

		Widget rootWidget = GetRootWidget();
		if (!rootWidget)
		{
			Print("Error in layout creation", LogLevel.ERROR);
			return;
		}

		/*
			Close button
		*/

		SCR_ButtonTextComponent buttonClose = SCR_ButtonTextComponent.GetButtonText(BUTTON_CLOSE, rootWidget);
		if (buttonClose)
			buttonClose.m_OnClicked.Insert(Close);
		else
			Print("Button Close not found - won't be able to exit by button", LogLevel.WARNING);

		/*
			Action button
		*/

		SCR_ButtonTextComponent buttonAction = SCR_ButtonTextComponent.GetButtonText(BUTTON_ACTION, rootWidget);
		if (buttonAction)
			buttonAction.m_OnClicked.Insert(ChangeText);
		else
			Print("Button Action not found - won't be able to interact by button", LogLevel.WARNING);
		
		/*
			ESC/Start listener
		*/

		InputManager inputManager = GetGame().GetInputManager();
		if (inputManager)
		{
			// this is for the menu/dialog to close when pressing ESC
			// an alternative is to have a button with the SCR_NavigationButtonComponent component
			// and its Action Name field set to MenuBack - this would activate the button on ESC press
			inputManager.AddActionListener("MenuOpen", EActionTrigger.DOWN, Close);
			inputManager.AddActionListener("MenuBack", EActionTrigger.DOWN, Close);
#ifdef WORKBENCH // in Workbench, F10 is used because ESC closes the preview
			inputManager.AddActionListener("MenuOpenWB", EActionTrigger.DOWN, Close);
			inputManager.AddActionListener("MenuBackWB", EActionTrigger.DOWN, Close);
#endif
		}
		else if (!buttonClose)
		{
			Print("Auto-closing the menu that has no exit path", LogLevel.WARNING);
			Close();
			return;
		}
	}

	//------------------------------------------------------------------------------------------------
	protected override void OnMenuClose()
	{
		// here we clean action listeners added above as the good practice wants it
		InputManager inputManager = GetGame().GetInputManager();
		if (inputManager)
		{
			inputManager.RemoveActionListener("MenuOpen", EActionTrigger.DOWN, Close);
			inputManager.RemoveActionListener("MenuBack", EActionTrigger.DOWN, Close);
#ifdef WORKBENCH
			inputManager.RemoveActionListener("MenuOpenWB", EActionTrigger.DOWN, Close);
			inputManager.RemoveActionListener("MenuBackWB", EActionTrigger.DOWN, Close);
#endif
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void ChangeText()
	{
		Widget rootWidget = GetRootWidget();
		if (!rootWidget)
			return;

		TextWidget terminal = TextWidget.Cast(rootWidget.FindWidget(TERMINAL));
		if (!terminal)
		{
			Print("Terminal could not be found", LogLevel.WARNING);
			return;
		}
		
		if (m_OpenCloseStateComponent.IsOpen())
			terminal.SetText("Laptop is open");
		else
			terminal.SetText("Laptop is closed");
	}
	
	//------------------------------------------------------------------------------------------------
	void SetOpenCloseStateComponent(AER_OpenCloseStateComponent component)
	{
		m_OpenCloseStateComponent = component;
	}
}