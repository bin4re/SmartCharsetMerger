#pragma once

#include <Common/tstring.h>

#include <atlbase.h> // 基本的ATL类
#include <atlwin.h>  // ATL窗口类
#include <atlapp.h>  // WTL 主框架窗口类
#include <atlctrls.h>
#include <atlcrack.h> // WTL 增强的消息宏

#include <vector>

class TListView : public CWindowImpl<TListView, CListViewCtrl> {
public:
    BEGIN_MSG_MAP_EX(TListView)
    MSG_WM_KEYDOWN(OnKeyDown)
    MESSAGE_HANDLER(WM_DROPFILES, OnDropFiles)
    END_MSG_MAP()

    void SetColumnText(int col, const std::tstring &s) noexcept;

    std::vector<int> GetSelectedItems() const;

    std::tstring GetItemText(int nItem, int nSubItem) const;

    void SelectAll() noexcept;

    LRESULT OnDropFiles(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) {
        SendMessage(GetParent(), uMsg, wParam, lParam);
        return 0;
    }

    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
        // Ctrl+A 全选
        if (nChar == 'A' && (GetKeyState(VK_CONTROL) & 0x8000)) {
            SelectAll();
            return;
        }
        SetMsgHandled(FALSE);
    }
};