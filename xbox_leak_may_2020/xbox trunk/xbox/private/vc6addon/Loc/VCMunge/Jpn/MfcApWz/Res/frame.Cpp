// $$frame_ifile$$.cpp : $$FRAME_CLASS$$ �N���X�̓���̒�`���s���܂��B
//

#include "stdafx.h"
#include "$$root$$.h"

#include "$$frame_hfile$$.h"
$$IF(PROJTYPE_SDI)
$$IF(PROJTYPE_EXPLORER)
#include "$$treeview_hfile$$.h"
#include "$$view_hfile$$.h"
$$ENDIF
$$ENDIF

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// $$FRAME_CLASS$$

$$IF(PROJTYPE_MDI || NODOCVIEW)
IMPLEMENT_DYNAMIC($$FRAME_CLASS$$, $$FRAME_BASE_CLASS$$)
$$ELSE
IMPLEMENT_DYNCREATE($$FRAME_CLASS$$, $$FRAME_BASE_CLASS$$)
$$ENDIF

BEGIN_MESSAGE_MAP($$FRAME_CLASS$$, $$FRAME_BASE_CLASS$$)
	//{{AFX_MSG_MAP($$FRAME_CLASS$$)
$$IF(VERBOSE)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
$$ENDIF
	ON_WM_CREATE()
$$IF(PROJTYPE_SDI)
$$IF(NODOCVIEW)
	ON_WM_SETFOCUS()
$$ENDIF 
$$ENDIF 
	//}}AFX_MSG_MAP
$$IF(HELP)
	// �O���[�o�� �w���v �R�}���h
	ON_COMMAND(ID_HELP_FINDER, $$FRAME_BASE_CLASS$$::OnHelpFinder)
	ON_COMMAND(ID_HELP, $$FRAME_BASE_CLASS$$::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, $$FRAME_BASE_CLASS$$::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, $$FRAME_BASE_CLASS$$::OnHelpFinder)
$$ENDIF
$$IF(PROJTYPE_SDI)
$$IF(PROJTYPE_EXPLORER)
$$IF(CListView)
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
$$ENDIF
$$ENDIF
$$ENDIF
END_MESSAGE_MAP()
$$IF(STATUSBAR)

static UINT indicators[] =
{
	ID_SEPARATOR,           // �X�e�[�^�X ���C�� �C���W�P�[�^
$$IF(DO_KANA)
	ID_INDICATOR_KANA,
$$ENDIF	// DO_KANA
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
$$ENDIF //STATUSBAR

/////////////////////////////////////////////////////////////////////////////
// $$FRAME_CLASS$$ �N���X�̍\�z/����

$$FRAME_CLASS$$::$$FRAME_CLASS$$()
{
$$IF(VERBOSE)
	// TODO: ���̈ʒu�Ƀ����o�̏����������R�[�h��ǉ����Ă��������B
	
$$ENDIF
}

$$FRAME_CLASS$$::~$$FRAME_CLASS$$()
{
}

int $$FRAME_CLASS$$::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if ($$FRAME_BASE_CLASS$$::OnCreate(lpCreateStruct) == -1)
		return -1;
$$IF(PROJTYPE_SDI)
$$IF(NODOCVIEW)
	// �t���[���̃N���C�A���g�̈�S�̂��߂�r���[���쐬���܂��B
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
$$ENDIF 
$$ENDIF //SDI + NODOCVIEW
$$IF(TOOLBAR)

$$IF(REBAR)
	if (!m_wndToolBar.CreateEx(this) ||
$$ELSE
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
$$ENDIF //REBAR
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // �쐬�Ɏ��s
	}
$$IF(REBAR)
$$IF( CONTAINER || CONTAINER_SERVER)
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() & ~CBRS_HIDE_INPLACE);
$$ENDIF // ANY CONTAINER
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// �쐬�Ɏ��s
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // �쐬�Ɏ��s
	}
$$IF( CONTAINER || CONTAINER_SERVER)
	m_wndReBar.SetBarStyle(m_wndReBar.GetBarStyle() & ~CBRS_HIDE_INPLACE);
$$ENDIF// ANY CONTAINER
$$ENDIF //REBAR
$$ENDIF //TOOLBAR
$$IF(STATUSBAR)

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // �쐬�Ɏ��s
	}
$$ENDIF //STATUSBAR
$$IF(TOOLBAR)

$$IF(REBAR)
$$IF(VERBOSE)	
	// TODO: �����c�[�� �`�b�v�X���K�v�Ȃ��ꍇ�A�������폜���Ă��������B
$$ENDIF
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)
	m_wndDlgBar.SetBarStyle(m_wndDlgBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
$$ENDIF//MINI_SERVER || FULL_SERVER || CONTAINER_SERVER
$$ELSE
$$IF(VERBOSE)
	// TODO: �c�[�� �o�[���h�b�L���O�\�ɂ��Ȃ��ꍇ�͈ȉ��̂R�s���폜
	//       ���Ă��������B
$$ENDIF
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
$$ENDIF //REBAR
$$ENDIF //TOOLBAR	

	return 0;
}
$$IF(SPLITTER_SDI || PROJTYPE_EXPLORER )
$$IF(PROJTYPE_SDI)

BOOL $$FRAME_CLASS$$::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
$$IF(PROJTYPE_EXPLORER)
	// �����E�B���h�E���쐬���܂�
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS($$TREEVIEW_CLASS$$), CSize(100, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS($$VIEW_CLASS$$), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
$$ELSE //!PROJTYPE_EXPLORER
	return m_wndSplitter.Create( this,
$$IF(VERBOSE)
		2, 2,                 // TODO: �s�Ɨ�̐��𒲐����Ă��������B
		CSize( 10, 10 ),      // TODO: �ŏ��̋��T�C�Y�𒲐����Ă��������B
$$ELSE //!VERBOSE
		2, 2,
		CSize( 10, 10 ),
$$ENDIF //VERBOSE
		pContext );
$$ENDIF //PROJTYPE_EXPLORER
}
$$ENDIF //SDI
$$ENDIF //SPLITTER || EXPLORER

BOOL $$FRAME_CLASS$$::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !$$FRAME_BASE_CLASS$$::PreCreateWindow(cs) )
		return FALSE;
$$IF(VERBOSE)
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C�����āAWindow �N���X��X�^�C����
	//       �C�����Ă��������B

$$ENDIF //VERBOSE
$$IF(FRAME_STYLES)
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		$$FRAME_STYLE_FLAGS$$;

$$ENDIF //FRAME_STYLES
$$IF(PROJTYPE_SDI)
$$IF(NODOCVIEW)
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
$$ENDIF 
$$ENDIF //SDI + NODOCVIEW
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// $$FRAME_CLASS$$ �N���X�̐f�f

#ifdef _DEBUG
void $$FRAME_CLASS$$::AssertValid() const
{
	$$FRAME_BASE_CLASS$$::AssertValid();
}

void $$FRAME_CLASS$$::Dump(CDumpContext& dc) const
{
	$$FRAME_BASE_CLASS$$::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// $$FRAME_CLASS$$ ���b�Z�[�W �n���h��
$$IF(PROJTYPE_SDI)
$$IF(NODOCVIEW)
void $$FRAME_CLASS$$::OnSetFocus(CWnd* pOldWnd)
{
	// �r���[ �E�B���h�E�Ƀt�H�[�J�X��^���܂��B
	m_wndView.SetFocus();
}

BOOL $$FRAME_CLASS$$::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// �r���[�ɍŏ��ɃR�}���h����������@���^���܂��B
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// ��������Ȃ������ꍇ�ɂ̓f�t�H���g�̏������s���܂��B
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
$$ENDIF 
$$ENDIF //SDI + NODOCVIEW

$$IF(PROJTYPE_SDI)
$$IF(PROJTYPE_EXPLORER)
$$IF(CListView)
$$VIEW_CLASS$$* $$FRAME_CLASS$$::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	$$VIEW_CLASS$$* pView = DYNAMIC_DOWNCAST($$VIEW_CLASS$$, pWnd);
	return pView;
}

void $$FRAME_CLASS$$::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
$$IF(VERBOSE)
	// TODO: ���̃R�[�h��ύX�E�g�����āA View ���j���[�̑I������������
	// �悤�ɂ��Ă��������B
$$ENDIF //VERBOSE

	$$VIEW_CLASS$$* pView = GetRightPane(); 

$$IF(VERBOSE)
	// �����E���̃y�C�����쐬����Ȃ����r���[�ł͂Ȃ��Ȃ�A
	// ���͈̔͂ŃR�}���h�𖳌��ɂ��܂�
$$ENDIF //VERBOSE

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

$$IF(VERBOSE)
		// �����R�}���h�� ID_VIEW_LINEUP �Ȃ�΁A LVS_ICON or LVS_SMALLICON 
		// ���[�h�ɂȂ����ꍇ�����A���̃R�}���h��L���ɂ��܂�

$$ENDIF //VERBOSE
		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
$$IF(VERBOSE)
			// �����łȂ���΁A�h�b�g���g���ăr���[�̃X�^�C���𔽉f���܂�
$$ENDIF //VERBOSE
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void $$FRAME_CLASS$$::OnViewStyle(UINT nCommandID)
{
$$IF(VERBOSE)
	// TODO: ���̃R�[�h��ύX�E�g�����āA View ���j���[�̑I������������
	// �悤�ɂ��Ă��������B
$$ENDIF //VERBOSE
	$$VIEW_CLASS$$* pView = GetRightPane();

$$IF(VERBOSE)
	// �����E���̃y�C�����쐬����� $$VIEW_CLASS$$ �Ȃ�� �A
	// ���j���[ �R�}���h���������܂�
$$ENDIF //VERBOSE
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
$$IF(VERBOSE)
				// ���X�g �R���g���[���̃A�C�R�����O���b�h�ʒu�ɍ��킹�܂�
$$ENDIF //VERBOSE
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

$$IF(VERBOSE)
		// ���̃R�}���h�̓��X�g �R���g���[���̃X�^�C����ύX���܂�
$$ENDIF //VERBOSE
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

$$IF(VERBOSE)
		// �X�^�C���ύX; �E�B���h�E�͎����I�ɍĕ`�悵�܂�
$$ENDIF //VERBOSE
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}
$$ENDIF
$$ENDIF
$$ENDIF