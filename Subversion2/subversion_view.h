//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2009 by Eran Ifrah
// file name            : subversion_view.h
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifndef __subversion_page__
#define __subversion_page__

/**
@file
Subclass of SubversionPageBase, which is generated by wxFormBuilder.
*/

#include "subversion2_ui.h"
#include "svninfo.h"
#include "svncommand.h"
#include "svntreedata.h"

class Subversion2;
class wxMenu;

class SvnPageSelectionInfo
{

public:
	wxArrayString            m_paths;
	SvnTreeData::SvnNodeType m_selectionType;

public:
	SvnPageSelectionInfo() : m_selectionType(SvnTreeData::SvnNodeTypeInvalid) {}
	virtual ~SvnPageSelectionInfo() {}

	void Clear() {
		m_paths.Clear();
		m_selectionType = SvnTreeData::SvnNodeTypeInvalid;
	}
};

/** Implementing SubversionPageBase */
class SubversionView : public SubversionPageBase
{
	Subversion2*         m_plugin;
	wxTreeItemId         m_modifiedItems;
	SvnCommand           m_simpleCommand;
	SvnCommand           m_diffCommand;
	SvnPageSelectionInfo m_selectionInfo;

public:
	enum {
		SvnInfo_Tag,
		SvnInfo_Branch,
		SvnInfo_Info
	};

protected:
	void                     CreatGUIControls();
	void                     ClearAll();
	void                     DoAddNode(const wxString &title, int imgId, SvnTreeData::SvnNodeType nodeType, const wxArrayString &files);
	int                      DoGetIconIndex(const wxString &filename);
	SvnTreeData::SvnNodeType DoGetSelectionType(const wxArrayTreeItemIds &items);
	void                     DoGetPaths(const wxTreeItemId &parent, wxArrayString &paths);
	void                     DoLinkEditor();
	void DoChangeRootPathUI       (const wxString &path);
	void DoRootDirChanged    (const wxString &path);
	wxString DoGetCurRepoPath() const ;
protected:
	// Menu management
	void         CreateFileMenu      (wxMenu *menu);
	void         CreateRootMenu      (wxMenu *menu);
	void         CreateSecondRootMenu(wxMenu *menu);
	wxTreeItemId DoGetParentNode     (const wxString &filename, const wxTreeItemId& parent);
	wxTreeItemId DoFindChild         (const wxTreeItemId& parent, const wxString &name, const wxString &curpath);
	
protected:
	// Handlers for SubversionPageBase events.
	void OnChangeRootDir ( wxCommandEvent& event );
	void OnTreeMenu      ( wxTreeEvent&    event );
	void OnItemActivated ( wxTreeEvent&    event );

	// IDE Events
	void OnWorkspaceLoaded    (wxCommandEvent &event);
	void OnWorkspaceClosed    (wxCommandEvent &event);
	void OnClearOuptut        (wxCommandEvent &event);
	void OnRefreshView        (wxCommandEvent &event);
	void OnFileRenamed        (wxCommandEvent &event);
	void OnFileAdded          (wxCommandEvent &event);
	void OnSettings           (wxCommandEvent &event);
	void OnActiveEditorChanged(wxCommandEvent &event);
	void OnOpenFile           (wxCommandEvent &event);

	// Svn events
	void OnCommit             (wxCommandEvent &event);
	void OnUpdate             (wxCommandEvent &event);
	void OnRevert             (wxCommandEvent &event);
	void OnAdd                (wxCommandEvent &event);
	void OnDelete             (wxCommandEvent &event);
	void OnBranch             (wxCommandEvent &event);
	void OnTag                (wxCommandEvent &event);
	void OnResolve            (wxCommandEvent &event);
	void OnDiff               (wxCommandEvent &event);
	void OnPatch              (wxCommandEvent &event);
	void OnPatchDryRun        (wxCommandEvent &event);
	void OnStop               (wxCommandEvent &event);
	void OnCleanup            (wxCommandEvent &event);
	void OnShowSvnInfo        (wxCommandEvent &event);
	void OnCheckout           (wxCommandEvent &event);
	void OnIgnoreFile         (wxCommandEvent &event);
	void OnIgnoreFilePattern  (wxCommandEvent &event);
	void OnBlame              (wxCommandEvent &event);
	void OnLinkEditor         (wxCommandEvent &event);
	void OnSwitch             (wxCommandEvent &event);
	void OnProperties         (wxCommandEvent &event);
	void OnLog                (wxCommandEvent &event);
	void OnLock               (wxCommandEvent &event);
	void OnUnLock             (wxCommandEvent &event);
	void OnRootDirChanged     (wxCommandEvent& event);
	void OnRename             (wxCommandEvent& event);
	
	DECLARE_EVENT_TABLE()

	void OnStopUI         (wxUpdateUIEvent &event);
	void OnClearOuptutUI  (wxUpdateUIEvent &event);

public:
	/** Constructor */
	SubversionView( wxWindow* parent, Subversion2 *plugin);
	virtual ~SubversionView();

	void     DisconnectEvents();
	void     UpdateTree(const wxArrayString& modifiedFiles, const wxArrayString &conflictedFiles, const wxArrayString &unversionedFiles, const wxArrayString& newFiles, const wxArrayString& deletedFiles, const wxArrayString& lockedFiles);
	void     BuildTree();
	void     BuildTree(const wxString &root);
	wxString GetRootDir() const {
		return DoGetCurRepoPath();
	}
};

#endif // __subversion_page__
