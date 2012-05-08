/*
  ==============================================================================

  Copyright (c) 2012, Vinnie Falco <vinnie.falco@gmail.com>

  This file is provided under the terms of the MIT License:

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

  ==============================================================================
*/

CConsoleText::CConsoleText (LuaCore& luaCore)
  : m_luaCore (luaCore)
  , m_text (new TextEditor)
{
  setSize (400, 100);

  {
    TextEditor* c = m_text;
    c->setReadOnly (true);
    c->setMultiLine (true, true);
    c->setFont (16);
    c->setColour (TextEditor::backgroundColourId, Colours::transparentBlack);
    c->setColour (TextEditor::textColourId,       Colours::white);
    c->setColour (TextEditor::outlineColourId,    Colours::transparentBlack);
    c->setColour (TextEditor::shadowColourId,     Colour::fromRGBA (255, 255, 255, 32));
    c->setBounds (0, 0, 400, 100);
    addAndMakeVisible (c);
  }

  m_luaCore.addListener (this);
}

CConsoleText::~CConsoleText ()
{
  m_luaCore.removeListener (this);
}

void CConsoleText::resized ()
{
  m_text->setBounds (0, 0, getWidth (), getHeight ());
}

void CConsoleText::onLuaCoreOutput (String text)
{
  m_text->moveCaretToEnd ();

  if (text != String::empty)
  {
    m_text->insertTextAtCaret (text);
    m_text->insertTextAtCaret ("\n");
  }
}
