/*
 * Copyright (c) 2003-2007 Rony Shapiro <ronys@users.sourceforge.net>.
 * All rights reserved. Use of the code is allowed under the
 * Artistic License terms, as specified in the LICENSE file
 * distributed with this code, or available from
 * http://www.opensource.org/licenses/artistic-license.php
 */
#pragma once

#include "afxwin.h"
#include "resource.h"
#include "resource2.h"  // Menu, Toolbar & Accelerator resources
#include "resource3.h"  // String resources
#include "afxdtctl.h" // only needed for date/time controls
#include "corelib\MyString.h"

class CExpDTDlg
	: public CDialog
{

public:
	CExpDTDlg(CWnd* pParent = NULL)
		: CDialog(CExpDTDlg::IDD, pParent), m_tttLTime(time_t(0))
            {};   // standard constructor

	CDateTimeCtrl m_pTimeCtl;                // time picker control
	CDateTimeCtrl m_pDateCtl;                // date picker control
	CMyString m_ascLTime;
	time_t m_tttLTime;

// Dialog Data
	enum { IDD = IDD_PICKEXPDATETIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

};
