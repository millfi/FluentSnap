#include <Windows.h>

// Windows.h のマクロと WinRT のメソッド名が衝突するのを防ぐ
#undef GetCurrentTime

#include <cstdint>
#include <vector>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.h>
#include <winrt/Microsoft.UI.Input.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Input;
using namespace Microsoft::UI::Xaml::Markup;
using namespace Microsoft::UI::Xaml::Media;
using namespace Microsoft::UI::Xaml::Shapes;
using namespace Microsoft::UI::Xaml::XamlTypeInfo;


class App : public ApplicationT<App, IXamlMetadataProvider> {
public:
    void OnLaunched(LaunchActivatedEventArgs const&) {
        // WinUI 3 のモダンなスタイル（テーマリソース）を読み込む
        Resources().MergedDictionaries().Append(XamlControlsResources());

        // 空のウィンドウを作成して表示
        window = Window();
        window.Title(L"My Screen Capture");
        window.Activate();
    }

    // --- 以下3つは標準コントロールの型解決用のお決まり実装 ---
    IXamlType GetXamlType(Windows::UI::Xaml::Interop::TypeName const& type) {
        return provider.GetXamlType(type);
    }
    IXamlType GetXamlType(hstring const& fullName) {
        return provider.GetXamlType(fullName);
    }
    com_array<XmlnsDefinition> GetXmlnsDefinitions() {
        return provider.GetXmlnsDefinitions();
    }

private:
    Window window{ nullptr };
    XamlControlsXamlMetaDataProvider provider;
};

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
    // WinRT の初期化（シングルスレッドアパートメント）
    init_apartment(apartment_type::single_threaded);

    // WinUI 3 のメッセージループを開始
    Application::Start([](auto&&) {
        make<App>();
        });

    return 0;
}