//
//  BionicSX2 iOS Entry Point
//  This is a minimal iOS app entry point that will later be expanded
//  to include the full PCSX2 emulator core.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface BionicSX2AppDelegate : UIResponder <UIApplicationDelegate>
@property (nonatomic, strong) UIWindow *window;
@end

@implementation BionicSX2AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.window.backgroundColor = [UIColor blackColor];

    // TODO: Initialize PCSX2 core here
    // For now, just show a simple view
    UIViewController *vc = [[UIViewController alloc] init];
    vc.view.backgroundColor = [UIColor blackColor];
    self.window.rootViewController = vc;
    [self.window makeKeyAndVisible];

    return YES;
}

@end

int main(int argc, char *argv[]) {
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([BionicSX2AppDelegate class]));
    }
}
