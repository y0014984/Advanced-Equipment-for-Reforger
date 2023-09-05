class AER_TerminalUI : MenuBase
{
	protected static const string TERMINAL_OUTPUT = "TerminalOutput";
	protected static const string TERMINAL_INPUT = "TerminalInput";
	protected static const string BUTTON_CLOSE = "ButtonClose";
	protected static const string BUTTON_ACTION = "ButtonAction";
	
	protected AER_OpenCloseStateComponent m_OpenCloseStateComponent;
	protected AER_PowerStateComponent m_PowerStateComponent;
	protected AER_FilesystemComponent m_FilesystemComponent;
	protected AER_TerminalComponent m_TerminalComponent;
	
	protected TextWidget m_TerminalOutputWidget;
	protected EditBoxWidget m_TerminalInputWidget;

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
			buttonAction.m_OnClicked.Insert(UpdateTerminal);
		else
			Print("Button Action not found - won't be able to interact by button", LogLevel.WARNING);
		
		/*
			Terminal Output
		*/
		
		m_TerminalOutputWidget = TextWidget.Cast(rootWidget.FindWidget(TERMINAL_OUTPUT));
		if (!m_TerminalOutputWidget)
		{
			Print("Terminal Output could not be found", LogLevel.WARNING);
			return;
		}
		
		/*
			Terminal Input
		*/
		
		m_TerminalInputWidget = EditBoxWidget.Cast(rootWidget.FindWidget(TERMINAL_INPUT));
		if (!m_TerminalInputWidget)
		{
			Print("Terminal Input could not be found", LogLevel.WARNING);
			return;
		}
		
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
	protected void UpdateTerminalOutput()
	{	
		if(m_TerminalComponent)
		{
			string output = m_TerminalComponent.GetTerminalOutputBuffer();
			
			output += m_TerminalComponent.GetPrompt();
			
			m_TerminalOutputWidget.SetText(output);
		}
		else
		{
			m_TerminalOutputWidget.SetText("Components not initialized yet");
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void UpdateTerminal()
	{
		string commandLine = m_TerminalInputWidget.GetText();
		
		m_TerminalComponent.AddCommandLine(commandLine);
		
		m_TerminalComponent.ProcessCommandLine(commandLine);
		
		m_TerminalInputWidget.SetText("");
		
		UpdateTerminalOutput();
	}
	
	//------------------------------------------------------------------------------------------------
	void SetOpenCloseStateComponent(AER_OpenCloseStateComponent component)
	{
		m_OpenCloseStateComponent = component;
	}
	
	//------------------------------------------------------------------------------------------------
	void SetPowerStateComponent(AER_PowerStateComponent component)
	{
		m_PowerStateComponent = component;
	}
	
	//------------------------------------------------------------------------------------------------
	void SetFilesystemComponent(AER_FilesystemComponent component)
	{
		m_FilesystemComponent = component;
	}
	
	//------------------------------------------------------------------------------------------------
	void SetTerminalComponent(AER_TerminalComponent component)
	{
		m_TerminalComponent = component;
		
		UpdateTerminalOutput();
	}
}