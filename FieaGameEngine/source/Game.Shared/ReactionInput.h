#pragma once

#include "Reaction.h"
#include "Factory.h"
#include "InputManager.h"

namespace FieaGameEngine
{
	class GameObject;

	class ReactionInput : public Reaction
	{
		RTTI_DECLARATIONS(ReactionInput, Reaction)

	public:
		static const std::string HorizontalAxisActions;
		static const std::string VerticalAxisActions;
		static const std::string WKeyActions;
		static const std::string AKeyActions;
		static const std::string SKeyActions;
		static const std::string DKeyActions;
		static const std::string SpaceKeyActions;
		static Vector<Signature> Signatures();

	public:
		explicit ReactionInput(const std::string& name = std::string());
		ReactionInput(const ReactionInput& other);
		ReactionInput(ReactionInput&& other);
		ReactionInput& operator=(const ReactionInput&) = default;
		ReactionInput& operator=(ReactionInput&&) = default;
		virtual ~ReactionInput();

		virtual gsl::owner<ReactionInput*> Clone() const override;
		virtual void Notify(const EventPublisher& event) override;

	protected:
		explicit ReactionInput(RTTI::IdType type, const std::string& name = std::string());

		static const HashMap<InputManager::Inputs, std::string> sInputMappings;

		void ExecuteAction(InputManager::Inputs input);
	};

	CONCRETE_FACTORY(ReactionInput, Scope)
}
