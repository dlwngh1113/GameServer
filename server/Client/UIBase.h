#pragma once

namespace ClientFramework
{
	class UIBase
	{
	protected:
		SDL_Rect m_rect;
		UIBase* m_parent;
		std::vector<std::unique_ptr<UIBase>> m_children;

	public:
		UIBase();
		virtual ~UIBase();

	public:
		virtual void Initialize();
		virtual void Render();
		virtual void UpdateFrame();

		void ScrollWheel(const SDL_MouseWheelEvent& evt);
		void MouseClick(const SDL_MouseButtonEvent& evt);
		void MouseMove(const SDL_MouseMotionEvent& evt);

		virtual void OnMouseButtonDown();
		virtual void OnMouseButtonUp();
		virtual void OnMouseHover();
		virtual void OnMouseMove(Sint32 x, Sint32 y);

	public:
		void SetParentPosition(int x, int y);
		void SetSize(int width, int height);

	public:
		template<typename T>
		T* CreateChild();
	};

	template<typename T>
	inline T* UIBase::CreateChild()
	{
		m_children.emplace_back(std::make_unique<T>());
		T* child = (T*)m_children.back().get();
		child->m_parent = this;
		child->Initialize();

		return child;
	}
}
