#pragma once

#include <unordered_map>

namespace ToolKit
{
	class SignalId
	{
	public:
		SignalId(int id);
		bool operator== (const SignalId& rhs);

	public:
		int m_id;
	};

	class State
	{
	public:
		State(std::string name);
		~State();
		virtual void TransitionIn(State* prevState) = 0;
		virtual void TransitionOut(State* nextState) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual State* Signaled(SignalId signal) = 0;

	public:
		SignalId m_currentSignal;
		std::string m_name;

	private:
		static std::vector<std::string> m_nameBuffer;
	};

	class StateMachine
	{
	public:
		StateMachine();
		~StateMachine();

		void Signal(SignalId signal);
		bool QueryState(std::string stateName);
		void PushState(State* state);
		void Update(float deltaTime);

	public:
		State* m_currentState;

	private:
		std::unordered_map<std::string, State*> m_states;
	};
}