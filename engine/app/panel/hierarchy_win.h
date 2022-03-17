#pragma once
#include <map>
#include "../../engine/core/config.h"
#include "../../engine/core/data/tree.h"
#include "../../editor/editor_base.h"
#include "../../editor/editor_container.h"

namespace Tara {
    class TARA_API Scene;
    class TARA_API SceneObject;

    namespace UI {
        enum class MouseButton;


        /// <summary>
        /// <para> Hierarchy shows the structure of current loaded scenes. </para>
        /// <para> User can modify the structures of order, name, and filtering by string to it. </para>
        /// </summary>
        class HierarchyWindow : public ImGui_WindowBase {
        public:
            HierarchyWindow();
            void Content() override;
            /// <summary>
            /// Hierachy scene object list child window state.
            /// </summary>
            ImGui_WindiwFlags childWinFlags = ImGui_WindiwFlags();
            /// <summary>
            /// Right click scene object field window state.
            /// </summary>
            ImGui_WindiwFlags fieldPopup = ImGui_WindiwFlags();


        protected:
            virtual void TopMenu(Scene* scene);
            virtual void OnClickField(SceneObject* so, MouseButton button);
            /// <summary>
            /// <para> Adding object in multiple select array. </para>
            /// <para> Depends on target object in the select list. </para>
            /// <para> Remove. if it's in select list. </para>
            /// <para> Append. if it's not in select list.  </para>
            /// <para> Default: effect panel global state is true </para>
            /// </summary>
            /// <param name="so">Adding scene object target.</param>
            virtual void MultipleSelect(SceneObject* so);
            /// <summary>
            /// <para> Adding object in multiple select array. </para>
            /// <para> Default: effect panel global state is false </para>
            /// </summary>
            /// <param name="so">Adding scene object target.</param>
            /// <param name="state">Apply the state into select array</param>
            virtual void MultipleSelect(SceneObject* so, bool state);
            /// <summary>
            /// <para> Adding object in multiple select array. </para>
            /// </summary>
            /// <param name="so">Adding scene object target.</param>
            /// <param name="state">Apply the state into select array. </param>
            /// <param name="effectGlobal">When state is change, the global focused object will be changed as well.</param>
            void MultipleSelect(SceneObject* so, bool state, bool effectGlobal);
            /// <summary>
            /// The event pack always callback func.
            /// Use for recording the hierachy rendering order.
            /// </summary>
            /// <param name="so">Which scene object is drawing right now</param>
            virtual void OnAlways(SceneObject* so);
            /// <summary>
            /// Duplicate select array objects.
            /// </summary>
            void EditDuplicate();
            /// <summary>
            /// Duplicate select array objects.
            /// </summary>
            void EditDelete();
            /// <summary>
            /// <para> Get the tree structure of the scene, filtering by name search string. </para>
            /// <para> Notices that the root node will be nullptr. </para>
            /// </summary>
            /// <param name="scene">Target scene</param>
            /// <returns>A full tree structure for the scene</returns>
            virtual tree<SceneObject*> GetSearchTree(Scene* scene);
            /// <summary>
            /// <para> Get the tree structure of the scene object, filter by search string. </para>
            /// <para> It use depth-first-search to get all the elements. </para>
            /// </summary>
            /// <param name="so">Target object.</param>
            /// <param name="search">Search string.</param>
            /// <returns>A full tree structure for the scene object.</returns>
            virtual std::vector<SceneObject*> GetSearchTree(SceneObject* so, std::string search = "");


            /// <summary>
            /// The event pack that use for low level scene object render methods.
            /// </summary>
            ImGui_EventPack<SceneObject> events = ImGui_EventPack<SceneObject>();
            /// <summary>
            /// Selected list of scene objects.
            /// </summary>
            std::vector<SceneObject*> selects = std::vector<SceneObject*>();
            /// <summary>
            /// Right click context menu open state.
            /// </summary>
            bool open = false;
            /// <summary>
            /// Left click scene object field state.
            /// </summary>
            bool state = false;
            /// <summary>
            /// <para> Left click scene object field state index. </para>
            /// <para> 0: Shift key modified. </para>
            /// <para> 1: Ctrl key modified. </para>
            /// <para> 2: Normal Left click. </para>
            /// <para> 3: Nullptr click (error) </para>
            /// </summary>
            int32_t stateIndex = -1;
            /// <summary>
            /// Current left click scene object.
            /// </summary>
            SceneObject* current = nullptr;
            /// <summary>
            /// Start recording order
            /// </summary>
            bool startRecord = false;
            /// <summary>
            /// <para> The record of drawing. </para>
            /// <para> This will show all the scene objects in the hierachy which is display right now by order </para>
            /// </summary>
            std::vector<SceneObject*> record = std::vector<SceneObject*>();
            /// <summary>
            /// Scene search keyword.
            /// </summary>
            std::map<Scene*, std::string> m_Search = std::map<Scene*, std::string>();
            /// <summary>
            /// <para> Scene search keyword update state. </para>
            /// <para> If true, at the end of rendering, it try to update tree. </para>
            /// </summary>
            std::map<Scene*, bool> m_UpdateSearch = std::map<Scene*, bool>();
            /// <summary>
            /// <para> Scene filter tree result. </para>
            /// <para> If keyword is not NULL, this tree will getting render. </para>
            /// </summary>
            std::map<Scene*, tree<SceneObject*>> m_sceneFilteredTree = std::map<Scene*, tree<SceneObject*>>();
        };
    }
}