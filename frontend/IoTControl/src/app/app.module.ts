import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { RouterModule } from '@angular/router';
import { HttpClientModule } from '@angular/common/http';  // Ensure HttpClientModule is included
import { routes } from './app.routes';  // Import the routing configuration

@NgModule({
  declarations: [
    // Do not declare AppComponent or AccountComponent here
  ],
  imports: [
    BrowserModule,
    HttpClientModule,  // Ensure HttpClientModule is imported
    RouterModule.forRoot(routes)  // Configure routing for the app
  ],
  providers: [],
  bootstrap: []  // No need to bootstrap here
})
export class AppModule {}
