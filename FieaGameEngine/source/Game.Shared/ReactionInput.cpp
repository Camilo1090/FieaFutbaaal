#include "pch.h"
#include "ReactionInput.h"
#include "Event.h"
#include "World.h"
#include "GameObject.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionInput)

	const std::string ReactionInput::WKeyActions = "WKeyAction";
	const std::string ReactionInput::AKeyActions = "AKeyAction";
	const std::string ReactionInput::SKeyActions = "SKeyAction";
	const std::string ReactionInput::DKeyActions = "DKeyAction";

	Vector<Signature> ReactionInput::Signatures()
	{
		return Vector<Signature>();
	}

	const HashMap<InputManager::Inputs, std::string> ReactionInput::sInputMappings = {
		{ InputManager::Inputs::W_KEY, ReactionInput::WKeyActions },
		{ InputManager::Inputs::A_KEY, ReactionInput::AKeyActions },
		{ InputManager::Inputs::S_KEY, ReactionInput::SKeyActions },
		{ InputManager::Inputs::D_KEY, ReactionInput::DKeyActions }
	};

	ReactionInput::ReactionInput(const std::string& name) : ReactionInput(TypeIdClass(), name)
	{
	}

	ReactionInput::ReactionInput(const ReactionInput& other) : Reaction(other)
	{
		Event<InputManager*>::Subscribe(*this);
	}

	ReactionInput::ReactionInput(ReactionInput&& other) : Reaction(std::move(other))
	{
		Event<InputManager*>::Subscribe(*this);
	}

	ReactionInput::~ReactionInput()
	{
		Event<InputManager*>::Unsubscribe(*this);
	}

	gsl::owner<ReactionInput*> ReactionInput::Clone() const
	{
		return new ReactionInput(*this);
	}

	void ReactionInput::Notify(const EventPublisher& event)
	{
		auto actualEvent = event.As<Event<InputManager*>>();
		if (actualEvent != nullptr)
		{
			//auto message = actualEvent->Message();
			//message->IsKeyPressed(InputManager::Inputs::W_KEY);
		}
	}

	ReactionInput::ReactionInput(RTTI::IdType type, const std::string& name) : Reaction(type, name)
	{
		Event<InputManager*>::Subscribe(*this);
	}

	void ReactionInput::ExecuteAction(InputManager::Inputs /*input*/)
	{
		//Datum& datum = At(sInputMappings.At(input));
	}
}
