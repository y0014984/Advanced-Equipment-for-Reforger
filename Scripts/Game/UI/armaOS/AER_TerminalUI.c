class AER_TerminalUI : MenuBase
{
	protected static const string TERMINAL_OUTPUT = "TerminalOutput";
	protected static const string TERMINAL_INPUT = "TerminalInput";
	protected static const string BUTTON_CLOSE = "ButtonClose";
	
	protected AER_OpenCloseStateComponent m_OpenCloseStateComponent;
	protected AER_PowerStateComponent m_PowerStateComponent;
	protected AER_FilesystemComponent m_FilesystemComponent;
	protected AER_TerminalComponent m_TerminalComponent;
	
	protected TextWidget m_TerminalOutputWidget;
	protected EditBoxWidget m_TerminalInputWidget;
	
	protected static const int TERMINAL_MAX_CHAR_WIDTH = 88;
	protected static const int TERMINAL_MAX_CHAR_HEIGHT = 28;
	
	protected static const int TERMINAL_FONT_SIZE = 24;
	protected static const float TERMINAL_FONT_CHAR_WIDTH = 14.5689655172;
	protected static const float TERMINAL_FONT_CHAR_HEIGHT = 25.7222222222;
	
	protected static const int TERMINAL_INPUT_EDITBOX_POS_X = 319;
	protected static const int TERMINAL_INPUT_EDITBOX_POS_Y = 231;
	
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

		AER_ButtonComponent buttonComponent = AER_ButtonComponent.GetButtonComponent(BUTTON_CLOSE, rootWidget);
		if (buttonComponent)
			buttonComponent.m_OnClick.Insert(OnClickInvoke);
		else
			Print("Button Close not found - won't be able to exit by button", LogLevel.WARNING);

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
		
		AER_EditBoxComponent editBoxComponent = AER_EditBoxComponent.GetEditBoxComponent(TERMINAL_INPUT, rootWidget);
		if (editBoxComponent)
		{
			editBoxComponent.m_OnChange.Insert(OnChangeInvoke);
		}
		else
			Print("EditBoxComponent not found - won't be able to interact by button", LogLevel.WARNING);
		
		Print("AER Added Focus and Write Mode Hack");
		GetGame().GetCallqueue().CallLater(SetFocusAndWriteMode, 250, true);
		
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
		else if (!buttonComponent)
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
		
		Print("AER Removed Focus and Write Mode Hack");
		GetGame().GetCallqueue().Remove(SetFocusAndWriteMode);
	}

	//------------------------------------------------------------------------------------------------	
	protected void UpdateTerminalOutput()
	{	
		string output = m_TerminalComponent.GetTerminalOutputBuffer();
			
		output += m_TerminalComponent.GetPrompt();
			
		output += m_TerminalComponent.GetCommandLineBuffer();
			
		m_TerminalOutputWidget.SetText(output);
		
		UpdateInputEditBoxPosAndSize();
	}

	//------------------------------------------------------------------------------------------------
	protected void UpdateTerminal()
	{
		m_TerminalComponent.ProcessCommandLine();
		
		UpdateTerminalOutput();

		m_TerminalInputWidget.SetText("");
	}
	
	//------------------------------------------------------------------------------------------------
	protected void UpdateInputEditBoxPosAndSize()
	{
		string terminalOutputBuffer = m_TerminalComponent.GetTerminalOutputBuffer();

		array<string> terminalOutputBufferLines = {};
		terminalOutputBuffer.Split("\n", terminalOutputBufferLines, false);
		
		int terminalOutputBufferLinesCount = terminalOutputBufferLines.Count();
		
		int promptLength = m_TerminalComponent.GetPrompt().Length();
		
		float posX = FrameSlot.GetPosX(m_TerminalInputWidget);
		float posY = FrameSlot.GetPosY(m_TerminalInputWidget);
		
		posX = TERMINAL_INPUT_EDITBOX_POS_X + (promptLength * TERMINAL_FONT_CHAR_WIDTH);
		posY = TERMINAL_INPUT_EDITBOX_POS_Y + ((terminalOutputBufferLinesCount - 1) * TERMINAL_FONT_CHAR_HEIGHT);
				
		float sizeX = (TERMINAL_MAX_CHAR_WIDTH - promptLength) * TERMINAL_FONT_CHAR_WIDTH;
		float sizeY = TERMINAL_FONT_CHAR_HEIGHT;
		
		FrameSlot.SetPos(m_TerminalInputWidget, posX, posY);
		FrameSlot.SetSize(m_TerminalInputWidget, sizeX, sizeY);
	}

	//------------------------------------------------------------------------------------------------
	protected void UpdateCommandLine()
	{
		string commandLine = m_TerminalInputWidget.GetText();
		
		m_TerminalComponent.SetCommandLineBuffer(commandLine);
		
		UpdateTerminalOutput();
	}
	
	//------------------------------------------------------------------------------------------------
	protected void SetFocusAndWriteMode()
	{
		if (GetRootWidget().GetWorkspace().GetFocusedWidget() != m_TerminalInputWidget)
			GetRootWidget().GetWorkspace().SetFocusedWidget(m_TerminalInputWidget);
		
		if (!m_TerminalInputWidget.IsInWriteMode())
			m_TerminalInputWidget.ActivateWriteMode();
		
		//PrintFormat("GetFocusedWidget: %1", GetGame().GetWorkspace().GetFocusedWidget());
		//PrintFormat("IsInWriteMode: %1", m_TerminalInputWidget.IsInWriteMode());
		//PrintFormat("IsEnabled: %1", m_TerminalInputWidget.IsEnabled());
	}

	//------------------------------------------------------------------------------------------------
	protected void OnClickInvoke(Widget w, int x, int y, int button)
	{
		m_TerminalComponent.SyncTerminalData();
		
		m_TerminalComponent.SetInUse(false);
		
		Close();
	}
	
	//------------------------------------------------------------------------------------------------
	protected void OnChangeInvoke(Widget w, int x, int y, bool finished)
	{
		if(finished)
			UpdateTerminal();
		else
			UpdateCommandLine();
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