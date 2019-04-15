#include "Headers/StoryBoard.h"
#include <algorithm>

void Storyboard::addNote(std::unique_ptr<Note> note)
{
    m_Notes.push_back(std::shared_ptr<Note>(std::move(note)));
}

void Storyboard::deleteNote(std::weak_ptr<Note> note)
{
    auto noteLocked = note.lock();
    if(noteLocked != nullptr)
    {
        std::remove(m_Notes.begin(), m_Notes.end(), noteLocked);
    }
}

std::vector<std::weak_ptr<Note>> Storyboard::searchByTitle(const std::string& title) const
{
    std::vector<std::weak_ptr<Note>> result;
    auto applyFunction = [&result, &title]
    (const std::shared_ptr<Note>& note){
        if(note->Title == title)
        {
            result.push_back(note);
        }
    };
    std::for_each(m_Notes.cbegin(), m_Notes.cend(), applyFunction);
    return result;
}

std::vector<std::weak_ptr<Note>> Storyboard::searchByText(const std::string& text) const
{
    std::vector<std::weak_ptr<Note>> result;
    auto applyFunction = [&result, &text]
    (const std::shared_ptr<Note>& note){
        if(note->Text == text)
        {
            result.push_back(note);
        }
    };
    std::for_each(m_Notes.cbegin(), m_Notes.cend(), applyFunction);
    return result;
}

std::vector<std::weak_ptr<Note>> Storyboard::searchByTag(const std::initializer_list<std::string>& tags) const
{
    std::vector<std::weak_ptr<Note>> result;
    auto applyFunction = [&result, &tags]
    (const std::shared_ptr<Note>& note){
        if(std::includes(note->Tags.cbegin(), note->Tags.cend(), tags.begin(), tags.end()))
        {
            result.push_back(note);
        }
    };
    std::for_each(m_Notes.cbegin(), m_Notes.cend(), applyFunction);
    return result;
}