//
//  main.m
//  dyld-app
//
//  Created by Misha Nya on 21.10.2023.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"


@import fuckme_dynamic;

int main(int argc, char * argv[]) {
    //dyld4::
    //_make_shit((const char **)argv);
    [FFFLoader new];
	NSString * appDelegateClassName;
	@autoreleasepool {
	    // Setup code that might create autoreleased objects goes here.
	    appDelegateClassName = NSStringFromClass([AppDelegate class]);
	}
	return UIApplicationMain(argc, argv, nil, appDelegateClassName);
}
