#pragma once

#include <memory>
#include "Note.h"

class Storyboard
{

public:

	void addNote(std::unique_ptr<Note> note);
	void deleteNote(std::weak_ptr<Note> note);
	std::vector<std::weak_ptr<Note>> searchByTitle(const std::string& title) const;
	std::vector<std::weak_ptr<Note>> searchByText(const std::string& text) const;
	std::vector<std::weak_ptr<Note>> searchByTag(const std::initializer_list<std::string>& tags) const;

private:

	std::vector<std::shared_ptr<Note>> m_Notes;

};