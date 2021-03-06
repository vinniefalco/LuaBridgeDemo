//==============================================================================
/*
  https://github.com/vinniefalco/LuaBridge
  https://github.com/vinniefalco/LuaBridgeDemo
  
  Copyright (C) 2012, Vinnie Falco <vinnie.falco@gmail.com>

  License: The MIT License (http://www.opensource.org/licenses/mit-license.php)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
//==============================================================================


CConsoleText::CConsoleText (LuaState& luaState)
  : m_luaState (luaState)
  , m_text (new TextEditor)
{
  setSize (400, 100);

  {
    TextEditor* c = m_text;
    c->setReadOnly (true);
    c->setMultiLine (true, true);
    c->setFont (18);
    c->setColour (TextEditor::backgroundColourId,       Colours::transparentBlack);
    c->setColour (TextEditor::textColourId,             Colours::white);
    c->setColour (TextEditor::highlightColourId,        Colour::fromRGBA (0, 255, 255, 96));
    c->setColour (TextEditor::highlightedTextColourId,  Colours::white);
    c->setColour (TextEditor::outlineColourId,          Colours::transparentBlack);
    c->setColour (TextEditor::shadowColourId,           Colour::fromRGBA (255, 255, 255, 32));
    
    c->setBounds (0, 0, 400, 100);
    addAndMakeVisible (c);
  }

  m_luaState.addListener (this);
}

CConsoleText::~CConsoleText ()
{
  m_luaState.removeListener (this);
}

void CConsoleText::resized ()
{
  m_text->setBounds (0, 0, getWidth (), getHeight ());
}

void CConsoleText::onLuaStatePrint (String text)
{
  m_text->moveCaretToEnd ();
  m_text->insertTextAtCaret (text);
  m_text->insertTextAtCaret ("\n");
}
