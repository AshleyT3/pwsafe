/*
 * Copyright (c) 2003-2010 Rony Shapiro <ronys@users.sourceforge.net>.
 * All rights reserved. Use of the code is allowed under the
 * Artistic License 2.0 terms, as specified in the LICENSE file
 * distributed with this code, or available from
 * http://www.opensource.org/licenses/artistic-license-2.0.php
 */

/** \file DbSelectionPanel.cpp
* 
*/
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "./DbSelectionPanel.h"
#include "./OpenFilePickerValidator.h"
#include "./SafeCombinationCtrl.h"
#include "./wxutils.h"

DbSelectionPanel::DbSelectionPanel(wxWindow* parent, 
                                    const wxString& filePrompt,
                                    const wxString& filePickerCtrlTitle,
                                    unsigned rowsep) : wxPanel(parent), m_sc(0)
{
  wxSizerFlags borderFlags = wxSizerFlags().Border(wxLEFT|wxRIGHT, SideMargin);

  /* This doesn't work since the second Border() call overwrites all the
   * previous border values.  So now we have to insert separators by hand
   */
  //wxSizerFlags rowFlags = borderFlags.Border(wxBOTTOM, RowSeparation);

  wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
  panelSizer->AddSpacer(TopMargin);

  panelSizer->Add(new wxStaticText(this, wxID_ANY, filePrompt), borderFlags);
  panelSizer->AddSpacer(RowSeparation);
  COpenFilePickerValidator validator(m_filepath);
  panelSizer->Add(new wxFilePickerCtrl(this, wxID_ANY, wxEmptyString, 
                                          filePickerCtrlTitle,
                                          _("Password Safe Databases (*.psafe3; *.dat)|*.psafe3;*.dat|Password Safe Backups (*.bak)|*.bak|Password Safe Intermediate Backups (*.ibak)|*.ibak|All files (*.*; *)|*.*;*"), 
                                          wxDefaultPosition, wxDefaultSize, 
                                          wxFLP_DEFAULT_STYLE | wxFLP_USE_TEXTCTRL, 
                                          validator), borderFlags.Expand());
  panelSizer->AddSpacer(RowSeparation*rowsep);

  panelSizer->Add(new wxStaticText(this, wxID_ANY, _("Safe Combination:")), borderFlags);
  panelSizer->AddSpacer(RowSeparation);
  
  m_sc = new CSafeCombinationCtrl(this);
  m_sc->textCtrl->SetValidator(wxTextValidator(wxFILTER_NONE, &m_combination));
  panelSizer->Add(m_sc, borderFlags.Expand());
  
  SetSizerAndFit(panelSizer);
  
  //The parent window must call our TransferDataToWindow and TransferDataFromWindow
  m_parent->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
}

DbSelectionPanel::~DbSelectionPanel()
{
}

void DbSelectionPanel::SelectCombinationText()
{
  m_sc->textCtrl->SetFocus();
  m_sc->textCtrl->SetSelection(-1,-1);
}
