#include "stdafx.h"
#include "ToolKit.h"
#include "StateMachine.h"
#include "DebugNew.h"

ToolKit::SignalId::SignalId(int id)
{
	m_id = id;
}

bool ToolKit::SignalId::operator== (const SignalId& rhs)
{ 
	return m_id == rhs.m_id; 
}

std::vector<std::string> ToolKit::State::m_nameBuffer;

ToolKit::State::State(std::string name)
	: m_currentSignal(-1)
{
	assert(std::find(m_nameBuffer.begin(), m_nameBuffer.end(), name) == m_nameBuffer.end()); // Name must be unique.
	m_nameBuffer.push_back(m_name);
	m_name = name;
}

ToolKit::State::~State()
{
}

ToolKit::StateMachine::StateMachine()
{
}

ToolKit::StateMachine::~StateMachine()
{
	for (auto& state : m_states)
	{
		SafeDel(state.second);
	}
}

void ToolKit::StateMachine::Signal(SignalId signal)
{
	if (m_currentState == nullptr)
	{
		return;
	}

	State* nextState = m_currentState->Signaled(signal);
	if (nextState == nullptr)
	{
		return;
	}

	m_currentState->TransitionOut(nextState);
	nextState->TransitionIn(m_currentState);
	m_currentState = nextState;
}

bool ToolKit::StateMachine::QueryState(std::string stateName)
{
	return m_states.find(stateName) != m_states.end();
}

void ToolKit::StateMachine::PushState(State* state)
{
	assert(m_states.find(state->m_name) == m_states.end()); // Make sure states are unique.
	m_states[state->m_name] = state;
}

void ToolKit::StateMachine::Update(float deltaTime)
{
	if (m_currentState != nullptr)
	{
		m_currentState->Update(deltaTime);
	}
}