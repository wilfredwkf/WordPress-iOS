//
//  WPTableViewController.h
//  WordPress
//
//  Created by Brad Angelcyk on 5/22/12.
//

#import <UIKit/UIKit.h>
#import "Blog.h"
#import "SettingsViewController.h"

@interface WPTableViewController : UIViewController <UITableViewDataSource, UITableViewDelegate, NSFetchedResultsControllerDelegate, UIAlertViewDelegate, SettingsViewControllerDelegate>

@property (nonatomic, strong) Blog *blog;
@property (nonatomic, strong) UITableView *tableView;
@property (nonatomic, assign) BOOL incrementalLoadingSupported;
@property (nonatomic, assign) BOOL isScrolling;

- (void)promptForPassword;

/**
 The results controller is made available to the subclasses so they can access the data
 */
@property (nonatomic,readonly,strong) NSFetchedResultsController *resultsController;

/**
 Enables the swipe menu for cells
 */
@property (nonatomic) BOOL swipeActionsEnabled;

/**
 Enables the infinteScrolling
 */
@property (nonatomic) BOOL infiniteScrollEnabled;

/**
 The noResultsView is made available to subclasses so they can customize its content.
 */
@property (nonatomic, readonly, strong) UIView *noResultsView;

/**
 Sync content with the server
 
 Subclasses can call this method if they need to invoke a refresh, but it's not meant to be implemented by subclasses.
 Override syncItemsWithUserInteraction:success:failure: instead
 
 @param userInteraction Pass YES if the sync is generated by user action
 */
- (void)syncItemsWithUserInteraction:(BOOL)userInteraction;

/**
 Simulate a pull to refresh.
 
 Subclasses can call this method if they need to simulate a pull to refresh, but it is not meant to be implemented by subclasses.
 */
- (void)simulatePullToRefresh;

/// ----------------------------------------------
/// @name Methods that subclasses should implement
/// ----------------------------------------------

/**
 The NSManagedObjectContext to use.
 
 Optional. Only needed if there subclass needs a custom context.
 */
- (NSManagedObjectContext *)managedObjectContext;

/**
 The name of the cache to use for the NSFetchResultsController.
 
 Optiona. Only needed if the subclass is using multiple caches.
 */
- (NSString *)resultsControllerCacheName;

/**
 Core Data entity name used by NSFetchedResultsController
 
 e.g. Post, Page, Comment, ...
 
 Subclasses *MUST* implement this method
 */
- (NSString *)entityName;

/**
 When this content was last synced.
 
 @return a NSDate object, or nil if it's never been synced before
 */
- (NSDate *)lastSyncDate;

/**
 Custom fetch request for NSFetchedResultsController
 
 Optional. Only needed if there are custom sort descriptors or predicate
 */
- (NSFetchRequest *)fetchRequest;

/**
 The attribute name to use to group results into sections
 
 @see [NSFetchedResultsController initWithFetchRequest:managedObjectContext:sectionNameKeyPath:cacheName:] for more info on sectionNameKeyPath
 */
- (NSString *)sectionNameKeyPath;

/**
 Returns a new (unconfigured) cell for the table view.
 
 Optional. If a subclass doesn't implement this method, a UITableViewCell with the default style is used
 
 @return a new initialized cell ready to be configured
 */
- (UITableViewCell *)newCell;

/**
 Configure a table cell for a specific index path
 
 Subclasses *MUST* implement this method
 */
- (void)configureCell:(UITableViewCell *)cell atIndexPath:(NSIndexPath *)indexPath;

/**
 Performs syncing of items
 
 Subclasses *MUST* implement this method
 
 @param userInteraction true if the sync responds to a user action, like pull to refresh
 @param success A block that's executed if the sync was successful
 @param failure A block that's executed if there was any error
 */
- (void)syncItemsWithUserInteraction:(BOOL)userInteraction success:(void (^)())success failure:(void (^)(NSError *error))failure;

/**
 Returns a boolean indicating if the blog is syncing that type of item right now
 
 Optional. If a subclass doesn't implement this method, WPTableViewController tracks syncing internally.
 Subclasses might want to implement this if the objects are going to be synced from other parts of the app
 */
- (BOOL)isSyncing;

/**
 If the subclass supports infinite scrolling, and there's more content available, return YES.
 This is an optional method which returns NO by default
 
 @return YES if there is more content to load
 */
- (BOOL)hasMoreContent;

/**
 Load extra content for infinite scrolling
 
 Subclasses *MUST* implement this method if infiniteScrollingEnabled is YES
 
 @param success A block that's executed if the sync was successful
 @param failure A block that's executed if there was any error
 */
- (void)loadMoreWithSuccess:(void (^)())success failure:(void (^)(NSError *error))failure;

/**
 Configures the secondary view to show when you swipe on a cell
 
 Subclasses *MUST* implement this method if swipeActionsEnabled is YES
 */
- (void)configureSwipeView:(UIView *)swipeView forIndexPath:(NSIndexPath *)indexPath;

/**
 Removes the swipe view.
 
 Subclasses should call this method if one of the swipe actions needs to dismiss the secondary menu
 */
- (void)removeSwipeView:(BOOL)animated;

/**
 Returns the row animation style the tableview should use.
 
 Optional. If the sub class does not implment this method the default will be used.
 @return The row animation style that the tableview should use.
 */
- (UITableViewRowAnimation)tableViewRowAnimation;


/**
 Completely reset the resultsController. Useful if the fetchRequest needs to be recreated with a new predicate.
 */
- (void)resetResultsController;

@end